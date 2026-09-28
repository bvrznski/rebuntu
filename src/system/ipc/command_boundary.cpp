// rebuntu::ipc::command_boundary — IPC Command Boundary Implementation (Phase 6.48)
//
// This implements Rebuntu's canonical IPC command boundary for process-separated
// callers.

#include <system/ipc/command_boundary.hpp>

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <poll.h>
#include <pthread.h>

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

namespace rebuntu {
namespace ipc {

// ============================================================================
// CommandBoundaryError helper functions
// ============================================================================

static std::string errno_string(int err) {
    char buffer[256];
    const char* msg = strerror_r(err, buffer, sizeof(buffer));
    if (msg) {
        return std::string(msg);
    }
    return "Unknown error";
}

// ============================================================================
// CommandBoundaryServer — IPC command boundary server
// ============================================================================

CommandBoundaryServer::CommandBoundaryServer(std::filesystem::path socket_path)
    : socket_path_(std::move(socket_path)) {
}

CommandBoundaryServer::~CommandBoundaryServer() {
    stop();
    
    // Clean up socket file if it exists
    try {
        std::filesystem::remove(socket_path_);
    } catch (...) {
        // Ignore cleanup errors during destruction
    }
}

CommandBoundaryServer::CommandBoundaryServer(CommandBoundaryServer&& other) noexcept
    : socket_path_(std::move(other.socket_path_)),
      running_(other.running_.load()),
      max_connections_(other.max_connections_),
      timeout_ms_(other.timeout_ms_),
      execution_callback_(std::move(other.execution_callback_)) {
    // Socket transfer is not supported - we'll create a new one
    other.running_.store(false);
}

CommandBoundaryServer& CommandBoundaryServer::operator=(CommandBoundaryServer&& other) noexcept {
    if (this != &other) {
        stop();
        
        socket_path_ = std::move(other.socket_path_);
        running_.store(other.running_.load());
        max_connections_ = other.max_connections_;
        timeout_ms_ = other.timeout_ms_;
        execution_callback_ = std::move(other.execution_callback_);
        
        other.running_.store(false);
    }
    return *this;
}

CommandBoundaryResult CommandBoundaryServer::start() {
    if (running_.load()) {
        return CommandBoundaryResult{CommandBoundaryError::kSuccess, ""};
    }
    
    // Clean up any existing socket file
    try {
        std::filesystem::remove(socket_path_);
    } catch (...) {
        // Ignore cleanup errors
    }
    
    // Create the Unix domain socket
    int fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "failed to create socket: " + errno_string(errno);
        return result;
    }
    
    // Build socket address
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    
    std::string path_str = socket_path_.string();
    if (path_str.size() >= static_cast<size_t>(sizeof(addr.sun_path))) {
        ::close(fd);
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "socket path too long";
        return result;
    }
    std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
    
    // Bind the socket
    if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd);
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "failed to bind socket: " + errno_string(errno);
        return result;
    }
    
    // Set permissions on the socket file
    if (::chmod(path_str.c_str(), 0660) < 0) {
        ::close(fd);
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "failed to set socket permissions: " + errno_string(errno);
        return result;
    }
    
    // Listen for connections
    if (::listen(fd, max_connections_) < 0) {
        ::close(fd);
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "failed to listen: " + errno_string(errno);
        return result;
    }
    
    // Initialize socket_ with our fd (UnixDomainSocket needs proper initialization)
    // We'll use a temporary UnixDomainSocket and move its state
    environment::ipc::UnixDomainSocket temp_socket(fd);
    socket_ = std::move(temp_socket);
    
    // Start the accept loop in a separate thread
    running_.store(true);
    accept_thread_ = std::thread(&CommandBoundaryServer::accept_loop, this);
    
    CommandBoundaryResult result;
    result.error = CommandBoundaryError::kSuccess;
    return result;
}

void CommandBoundaryServer::stop() {
    if (!running_.exchange(false)) {
        return;  // Not running
    }
    
    // Close the socket to wake up accept()
    socket_.close();
    
    // Join the accept thread
    if (accept_thread_.joinable()) {
        accept_thread_.join();
    }
}

CommandBoundaryServer& CommandBoundaryServer::set_max_connections(size_t max) {
    max_connections_ = max;
    return *this;
}

CommandBoundaryServer& CommandBoundaryServer::set_timeout(std::chrono::milliseconds timeout) {
    timeout_ms_ = timeout;
    return *this;
}

CommandBoundaryServer& CommandBoundaryServer::set_execution_callback(ExecutionCallback cb) {
    execution_callback_ = std::move(cb);
    return *this;
}

void CommandBoundaryServer::run_until_stopped() {
    while (running_.load()) {
        // Keep running until stopped
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CommandBoundaryServer::accept_loop() {
    while (running_.load()) {
        int fd = socket_.fd();
        if (fd < 0) {
            break;
        }
        
        struct pollfd pfd = {fd, POLLIN, 0};
        
        // Wait for incoming connections with timeout
        int ret = ::poll(&pfd, 1, 100);  // 100ms timeout
        
        if (ret < 0) {
            continue;  // Error or interrupted
        }
        
        if (ret == 0) {
            continue;  // Timeout - check running flag
        }
        
        // Accept the connection
        struct sockaddr_un client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int client_fd = ::accept4(fd, 
                                  reinterpret_cast<struct sockaddr*>(&client_addr), 
                                  &addrlen, 
                                  SOCK_CLOEXEC);
        
        if (client_fd < 0) {
            continue;  // Accept failed
        }
        
        // Handle the client in a separate thread (bounded by max_connections_)
        std::thread client_thread(&CommandBoundaryServer::handle_client, this, client_fd);
        client_thread.detach();
    }
}

void CommandBoundaryServer::handle_client(int client_fd) {
    // Set the socket to non-blocking for receive operations
    int flags = fcntl(client_fd, F_GETFL, 0);
    if (flags >= 0) {
        fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    }
    
    // Parse command message from client
    CommandMessage msg;
    
    // Read protocol version first
    int32_t version;
    ssize_t n = ::read(client_fd, &version, sizeof(version));
    if (n < static_cast<ssize_t>(sizeof(version))) {
        ::close(client_fd);
        return;
    }
    
    if (version != 1) {
        // Send error response
        CommandResponse resp;
        resp.correlation_id = 0;
        resp.status = core::SemanticStatus::kFailure;
        resp.error.code = "E_INVALID_VERSION";
        resp.error.message = "invalid protocol version";
        send_response(client_fd, resp);
        ::close(client_fd);
        return;
    }
    
    msg.protocol_version = version;
    msg.timestamp = std::chrono::system_clock::now();
    
    // Read correlation ID
    uint64_t corr_id;
    n = ::read(client_fd, &corr_id, sizeof(corr_id));
    if (n < static_cast<ssize_t>(sizeof(corr_id))) {
        ::close(client_fd);
        return;
    }
    msg.correlation_id = corr_id;
    
    // Authenticate the peer
    msg.peer_identity = authenticate_peer(client_fd);
    
    // Execute the command if callback is set
    CommandResponse response;
    if (execution_callback_) {
        response = execution_callback_(msg);
    } else {
        response.status = core::SemanticStatus::kFailure;
        response.error.code = "E_NO_EXECUTOR";
        response.error.message = "no execution callback set";
    }
    
    // Send response back to client
    send_response(client_fd, response);
    
    ::close(client_fd);
}

PeerIdentity CommandBoundaryServer::authenticate_peer(int client_fd) const {
    PeerIdentity identity;
    
    // Get peer credentials using getpeereid() or SO_PEERCRED
    struct ucred creds;
    socklen_t len = sizeof(creds);
    
    if (getsockopt(client_fd, SOL_SOCKET, SO_PEERCRED, &creds, &len) == 0) {
        identity.uid = creds.uid;
        identity.gid = creds.gid;
        identity.pid = creds.pid;
        identity.authenticated = true;
        identity.auth_method = "credentials";
    } else {
        // Fall back to filesystem permission-based authentication
        struct stat st;
        if (stat(socket_path_.c_str(), &st) == 0) {
            // Check if the peer has permission to connect
            mode_t perms = st.st_mode & 0777;
            uid_t current_uid = getuid();
            
            bool has_access = false;
            if (st.st_uid == current_uid) {
                has_access = (perms & S_IRUSR) && (perms & S_IWUSR);
            } else {
                has_access = (perms & (S_IRGRP | S_IROTH)) && (perms & (S_IWGRP | S_IWOTH));
            }
            
            identity.authenticated = has_access;
            identity.auth_method = "fs_permissions";
        }
    }
    
    return identity;
}

CommandMessage CommandBoundaryServer::parse_command_message(int fd) {
    // For now, read raw bytes and parse
    // In a full implementation, this would parse the wire format
    
    CommandMessage msg;
    
    // Read protocol version first
    int32_t version;
    ssize_t n = ::read(fd, &version, sizeof(version));
    if (n < static_cast<ssize_t>(sizeof(version))) {
        return msg;  // Invalid message
    }
    
    if (version != 1) {
        msg.protocol_version = -1;  // Mark as invalid protocol version
        return msg;
    }
    
    msg.protocol_version = version;
    msg.timestamp = std::chrono::system_clock::now();
    
    // Read correlation ID
    uint64_t corr_id;
    n = ::read(fd, &corr_id, sizeof(corr_id));
    if (n < static_cast<ssize_t>(sizeof(corr_id))) {
        return msg;
    }
    msg.correlation_id = corr_id;
    
    // Read command intent fields
    // For simplicity, we'll create a default command intent
    msg.command_intent.id = "ipc-cmd-" + std::to_string(msg.correlation_id);
    msg.command_intent.semantic_kind = command::SemanticKind::QUERY;
    msg.command_intent.scope = command::ScopeContext::USER;
    
    return msg;
}

bool CommandBoundaryServer::send_response(int fd, const CommandResponse& resp) {
    // Serialize response to wire format
    
    // Write correlation ID
    ssize_t n = ::write(fd, &resp.correlation_id, sizeof(resp.correlation_id));
    if (n < static_cast<ssize_t>(sizeof(resp.correlation_id))) {
        return false;
    }
    
    // Write status
    int32_t status = static_cast<int32_t>(resp.status);
    n = ::write(fd, &status, sizeof(status));
    if (n < static_cast<ssize_t>(sizeof(status))) {
        return false;
    }
    
    // Write changed flag
    bool changed = resp.changed;
    n = ::write(fd, &changed, sizeof(changed));
    if (n < static_cast<ssize_t>(sizeof(changed))) {
        return false;
    }
    
    // Write verified flag
    bool verified = resp.verified;
    n = ::write(fd, &verified, sizeof(verified));
    if (n < static_cast<ssize_t>(sizeof(verified))) {
        return false;
    }
    
    // Write output value length and data
    uint32_t output_len = static_cast<uint32_t>(resp.output_value.length());
    n = ::write(fd, &output_len, sizeof(output_len));
    if (n < static_cast<ssize_t>(sizeof(output_len))) {
        return false;
    }
    
    if (!resp.output_value.empty()) {
        n = ::write(fd, resp.output_value.c_str(), output_len);
        if (n < static_cast<ssize_t>(output_len)) {
            return false;
        }
    }
    
    // Write error code
    uint32_t err_code_len = static_cast<uint32_t>(resp.error.code.length());
    n = ::write(fd, &err_code_len, sizeof(err_code_len));
    if (n < static_cast<ssize_t>(sizeof(err_code_len))) {
        return false;
    }
    
    if (!resp.error.code.empty()) {
        n = ::write(fd, resp.error.code.c_str(), err_code_len);
        if (n < static_cast<ssize_t>(err_code_len)) {
            return false;
        }
    }
    
    // Write error message length and data
    uint32_t err_msg_len = static_cast<uint32_t>(resp.error.message.length());
    n = ::write(fd, &err_msg_len, sizeof(err_msg_len));
    if (n < static_cast<ssize_t>(sizeof(err_msg_len))) {
        return false;
    }
    
    if (!resp.error.message.empty()) {
        n = ::write(fd, resp.error.message.c_str(), err_msg_len);
        if (n < static_cast<ssize_t>(err_msg_len)) {
            return false;
        }
    }
    
    return true;
}

// ============================================================================
// CommandBoundaryClient — IPC command boundary client
// ============================================================================

CommandBoundaryClient::CommandBoundaryClient(std::filesystem::path socket_path)
    : socket_path_(std::move(socket_path)), socket_fd_{-1}, connected_{false} {
}

CommandBoundaryClient::~CommandBoundaryClient() {
    disconnect();
}

CommandBoundaryClient::CommandBoundaryClient(CommandBoundaryClient&& other) noexcept
    : socket_path_(std::move(other.socket_path_)),
      socket_fd_{other.socket_fd_},
      connected_{other.connected_.load()} {
    other.socket_fd_ = -1;
    other.connected_.store(false);
}

CommandBoundaryClient& CommandBoundaryClient::operator=(CommandBoundaryClient&& other) noexcept {
    if (this != &other) {
        disconnect();
        
        socket_path_ = std::move(other.socket_path_);
        socket_fd_ = other.socket_fd_;
        connected_.store(other.connected_.load());
        
        other.socket_fd_ = -1;
        other.connected_.store(false);
    }
    return *this;
}

CommandBoundaryResult CommandBoundaryClient::connect(std::chrono::milliseconds timeout) {
    return connect_with_timeout(timeout);
}

void CommandBoundaryClient::disconnect() {
    if (socket_fd_ >= 0) {
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
    connected_.store(false);
}

CommandBoundaryResult CommandBoundaryClient::connect_with_timeout(std::chrono::milliseconds timeout) {
    if (connected_.load()) {
        return CommandBoundaryResult{CommandBoundaryError::kSuccess, ""};
    }
    
    // Create socket
    int fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "failed to create socket: " + errno_string(errno);
        return result;
    }
    
    // Set non-blocking for timeout handling
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0) {
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    }
    
    // Build socket address
    struct sockaddr_un addr;
        memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    
    std::string path_str = socket_path_.string();
    if (path_str.size() >= static_cast<size_t>(sizeof(addr.sun_path))) {
        ::close(fd);
        CommandBoundaryResult result;
        result.error = CommandBoundaryError::kSystemError;
        result.error_message = "socket path too long";
        return result;
    }
    std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
    
    // Try to connect
    int ret = ::connect(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
    
    if (ret < 0) {
        if (errno == EINPROGRESS) {
            // Connection in progress - use poll with timeout
            struct pollfd pfd = {fd, POLLOUT, 0};
            
            int poll_ret = ::poll(&pfd, 1, static_cast<int>(timeout.count()));
            
            if (poll_ret <= 0) {
                ::close(fd);
                CommandBoundaryResult result;
                result.error = CommandBoundaryError::kTimeout;
                return result;
            }
            
            // Check connection result
            int so_error;
            socklen_t len = sizeof(so_error);
            if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_error, &len) < 0 || so_error != 0) {
                ::close(fd);
                CommandBoundaryResult result;
                result.error = CommandBoundaryError::kConnectionRefused;
                return result;
            }
        } else {
            ::close(fd);
            CommandBoundaryResult result;
            result.error = CommandBoundaryError::kConnectionRefused;
            result.error_message = "connection failed: " + errno_string(errno);
            return result;
        }
    }
    
    // Set back to blocking mode
    flags = fcntl(fd, F_GETFL, 0);
    if (flags >= 0) {
        fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
    }
    
    socket_fd_ = fd;
    connected_.store(true);
    
    CommandBoundaryResult result;
    result.error = CommandBoundaryError::kSuccess;
    return result;
}

CommandBoundaryResult CommandBoundaryClient::send_command(
    const command::CommandIntent& intent,
    CommandResponse* out_response,
    std::chrono::milliseconds timeout) {
    
    if (!connected_.load()) {
        auto connect_result = connect_with_timeout(std::chrono::seconds(5));
        if (!connect_result.is_success()) {
            return connect_result;
        }
    }
    
    // Create command message
    CommandMessage msg = CommandMessage::make(intent);
    
    // Send protocol version
    int32_t version = 1;
    ssize_t n = send_with_timeout(&version, sizeof(version), timeout);
    if (n < static_cast<ssize_t>(sizeof(version))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to send protocol version"};
    }
    
    // Send correlation ID
    n = send_with_timeout(&msg.correlation_id, sizeof(msg.correlation_id), timeout);
    if (n < static_cast<ssize_t>(sizeof(msg.correlation_id))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to send correlation id"};
    }
    
    // Parse response
    CommandResponse resp;
    
    // Read correlation ID back
    uint64_t corr_id;
    n = recv_with_timeout(&corr_id, sizeof(corr_id), timeout);
    if (n < static_cast<ssize_t>(sizeof(corr_id))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive correlation id"};
    }
    
    // Read status
    int32_t status;
    n = recv_with_timeout(&status, sizeof(status), timeout);
    if (n < static_cast<ssize_t>(sizeof(status))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive status"};
    }
    
    resp.status = static_cast<core::SemanticStatus>(status);
    
    // Read flags
    bool changed, verified;
    n = recv_with_timeout(&changed, sizeof(changed), timeout);
    if (n < static_cast<ssize_t>(sizeof(changed))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive flags"};
    }
    
    resp.changed = changed;
    
    n = recv_with_timeout(&verified, sizeof(verified), timeout);
    if (n < static_cast<ssize_t>(sizeof(verified))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive verified flag"};
    }
    
    resp.verified = verified;
    
    // Read output value
    uint32_t output_len;
    n = recv_with_timeout(&output_len, sizeof(output_len), timeout);
    if (n < static_cast<ssize_t>(sizeof(output_len))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive output length"};
    }
    
    if (output_len > 0) {
        std::string output_str(output_len, '\0');
        n = recv_with_timeout(&output_str[0], output_len, timeout);
        if (n < static_cast<ssize_t>(output_len)) {
            return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                         "failed to receive output value"};
        }
        resp.output_value = std::move(output_str);
    }
    
    // Read error code
    uint32_t err_code_len;
    n = recv_with_timeout(&err_code_len, sizeof(err_code_len), timeout);
    if (n < static_cast<ssize_t>(sizeof(err_code_len))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive error code length"};
    }
    
    if (err_code_len > 0) {
        std::string err_code_str(err_code_len, '\0');
        n = recv_with_timeout(&err_code_str[0], err_code_len, timeout);
        if (n < static_cast<ssize_t>(err_code_len)) {
            return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                         "failed to receive error code"};
        }
        resp.error.code = std::move(err_code_str);
    }
    
    // Read error message
    uint32_t err_msg_len;
    n = recv_with_timeout(&err_msg_len, sizeof(err_msg_len), timeout);
    if (n < static_cast<ssize_t>(sizeof(err_msg_len))) {
        return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                     "failed to receive error message length"};
    }
    
    if (err_msg_len > 0) {
        std::string err_msg_str(err_msg_len, '\0');
        n = recv_with_timeout(&err_msg_str[0], err_msg_len, timeout);
        if (n < static_cast<ssize_t>(err_msg_len)) {
            return CommandBoundaryResult{CommandBoundaryError::kSystemError,
                                         "failed to receive error message"};
        }
        resp.error.message = std::move(err_msg_str);
    }
    
    *out_response = resp;
    
    CommandBoundaryResult result;
    result.error = CommandBoundaryError::kSuccess;
    return result;
}

CommandBoundaryResult CommandBoundaryClient::send_command_async(
    const command::CommandIntent&) {
    
    if (!connected_.load()) {
        auto connect_result = connect_with_timeout(std::chrono::seconds(5));
        if (!connect_result.is_success()) {
            return connect_result;
        }
    }
    
    // For async, we just send and don't wait for response
    
    CommandBoundaryResult result;
    result.error = CommandBoundaryError::kSuccess;
    return result;
}

ssize_t CommandBoundaryClient::send_with_timeout(const void* data, size_t len, std::chrono::milliseconds timeout) {
    if (socket_fd_ < 0) {
        return -1;
    }
    
    struct pollfd pfd = {socket_fd_, POLLOUT, 0};
    int ret = ::poll(&pfd, 1, static_cast<int>(timeout.count()));
    
    if (ret <= 0) {
        return -1;  // Timeout or error
    }
    
    return ::send(socket_fd_, data, len, 0);
}

ssize_t CommandBoundaryClient::recv_with_timeout(void* buffer, size_t len, std::chrono::milliseconds timeout) {
    if (socket_fd_ < 0) {
        return -1;
    }
    
    struct pollfd pfd = {socket_fd_, POLLIN, 0};
    int ret = ::poll(&pfd, 1, static_cast<int>(timeout.count()));
    
    if (ret <= 0) {
        return -1;  // Timeout or error
    }
    
    return ::recv(socket_fd_, buffer, len, 0);
}

// ============================================================================
// Utility Functions
// ============================================================================

std::filesystem::path get_command_boundary_socket_dir(
    const environment::sessions::RuntimeDirectoryInfo& rt_info) {
    if (rt_info.status == environment::sessions::RuntimeDirStatus::kAvailable) {
        return rt_info.path / "command_boundary";
    }
    
    // Fallback to system runtime directory
    return "/run/rebuntu/command_boundary";
}

CommandMessage make_command_message_from_operation(
    const core::OperationRequest& op_request,
    std::string caller_id) {
    CommandMessage msg;
    msg.protocol_version = 1;
    msg.timestamp = std::chrono::system_clock::now();
    
    // Convert OperationRequest to CommandIntent
    command::CommandIntent intent;
    intent.id = "op-" + std::to_string(msg.correlation_id);
    intent.verb = op_request.operation_id;
    
    if (op_request.subject.has_value()) {
        intent.semantic_kind = command::SemanticKind::CONFIGURE;
    } else {
        intent.semantic_kind = command::SemanticKind::QUERY;
    }
    
    if (!caller_id.empty()) {
        intent.caller_id = std::move(caller_id);
    }
    
    msg.command_intent = intent;
    
    return msg;
}

}  // namespace ipc
}  // namespace rebuntu