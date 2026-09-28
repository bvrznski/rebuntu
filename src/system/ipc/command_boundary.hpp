// rebuntu::ipc::command_boundary — IPC Command Boundary (Phase 6.48)
//
// This establishes Rebuntu's canonical IPC command boundary for process-separated
// callers:
//
//   IPC COMMAND BOUNDARY
//     - Accepts typed/versioned command messages over Unix domain sockets
//     - Authenticates peers via filesystem permissions and peer credentials
//     - Routes commands to canonical execution subsystem
//     - Maintains semantic integrity (DATA != CONTROL, MODEL OUTPUT != AUTHORITY)
//
//   CRITICAL INVARIENTS
//     - Authentication alone does NOT authorize operations
//     - All commands must pass through typed validation
//     - Execution requires separate authorization decision
//     - No arbitrary shell execution allowed
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/ipc/command_boundary.hpp
//
// Phase 6.48 extends Phase 2.12 (IPC), Phase 3.4 (semantic IPC protocol),
// and Phase 6.1 (typed command model).

#pragma once

#include <system/core/contracts.hpp>
#include <system/environment/ipc.hpp>
#include <system/command/model.hpp>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <utility>
#include <stdexcept>

namespace rebuntu {
namespace ipc {

// ============================================================================
// CommandBoundaryError - Error codes for IPC command boundary operations
// ============================================================================

enum class CommandBoundaryError {
    kSuccess,
    kInvalidProtocolVersion,
    kMalformedCommand,
    kUnknownCommand,
    kAuthenticationFailed,
    kAuthorizationDenied,
    kExecutionFailed,
    kTimeout,
    kWouldBlock,
    kServerShutdown,
    kConnectionRefused,
    kSystemError
};

struct CommandBoundaryResult {
    CommandBoundaryError error = CommandBoundaryError::kSuccess;
    std::string error_message;
    
    core::SemanticStatus semantic_status() const {
        switch (error) {
            case CommandBoundaryError::kSuccess:
                return core::SemanticStatus::kSuccess;
            case CommandBoundaryError::kInvalidProtocolVersion:
            case CommandBoundaryError::kMalformedCommand:
            case CommandBoundaryError::kAuthenticationFailed:
            case CommandBoundaryError::kAuthorizationDenied:
            case CommandBoundaryError::kTimeout:
            case CommandBoundaryError::kWouldBlock:
                return core::SemanticStatus::kFailure;
            default:
                return core::SemanticStatus::kUnknown;
        }
    }
    
    bool is_success() const {
        return semantic_status() == core::SemanticStatus::kSuccess;
    }
};

// ============================================================================
// PeerIdentity - Identity of an IPC peer
// ============================================================================

struct PeerIdentity {
    // File descriptor credentials (Unix domain sockets)
    uid_t uid = 0;           // Effective user ID
    gid_t gid = 0;           // Effective group ID  
    pid_t pid = 0;           // Process ID
    
    // Path-based authentication (from socket path ownership)
    std::string auth_method;  // "fs_permissions", "credentials", "token"
    
    // Authentication result
    bool authenticated{false};
    
    static PeerIdentity anonymous() {
        return PeerIdentity{};
    }
};

// ============================================================================
// CommandMessage - Typed command message over IPC
// ============================================================================

struct CommandMessage {
    // Protocol metadata
    int32_t protocol_version{1};     // Must match kProtocolVersion
    std::chrono::system_clock::time_point timestamp;
    
    // Correlation ID for request/response matching
    uint64_t correlation_id{0};
    
    // Caller information (populated by server, not trusted from client)
    PeerIdentity peer_identity;
    
    // Command payload
    command::CommandIntent command_intent;
    
    // Authentication evidence (provenance-bearing, NOT authority)
    std::string auth_token;  // Opaque reference only
    
    static CommandMessage make(const command::CommandIntent& intent) {
        CommandMessage msg;
        msg.protocol_version = 1;
        msg.timestamp = std::chrono::system_clock::now();
        // Use a simple hash based on the intent's string representation for correlation ID
        msg.correlation_id = std::hash<std::string>{}(intent.id);
        msg.command_intent = intent;
        return msg;
    }
};

// ============================================================================
// CommandResponse - Response to a command message
// ============================================================================

struct CommandResponse {
    uint64_t correlation_id{0};  // Matches request's correlation_id
    
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // Execution results
    std::string output_value;
    bool changed{false};
    bool verified{false};
    
    // Evidence supporting the result (provenance-bearing)
    std::vector<core::Evidence> evidence;
    
    // Error information
    core::Error error;
    
    // Timing
    std::chrono::milliseconds execution_time_ms{0};
    
    static CommandResponse success(const core::Evidence& ev = {}) {
        CommandResponse r;
        r.status = core::SemanticStatus::kSuccess;
        r.verified = true;
        if (!ev.source.empty()) {
            r.evidence.push_back(ev);
        }
        return r;
    }
    
    static CommandResponse no_change() {
        CommandResponse r;
        r.status = core::SemanticStatus::kSuccess;
        r.changed = false;
        r.verified = true;
        return r;
    }
    
    static CommandResponse failure(std::string code, std::string message) {
        CommandResponse r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    bool is_success() const {
        return status == core::SemanticStatus::kSuccess && verified;
    }
};

// ============================================================================
// CommandBoundaryServer — IPC command boundary server
//
// Listens on a Unix domain socket and accepts typed command messages from
// process-separated callers. Authenticates peers and routes to canonical
// execution.
// ============================================================================

class CommandBoundaryServer {
public:
    // Callback type for command execution
    using ExecutionCallback = std::function<CommandResponse(const CommandMessage&)>;

    explicit CommandBoundaryServer(std::filesystem::path socket_path);
    
    ~CommandBoundaryServer();
    
    // Move semantics only
    CommandBoundaryServer(CommandBoundaryServer&&) noexcept;
    CommandBoundaryServer& operator=(CommandBoundaryServer&&) noexcept;
    
    // Delete copy semantics
    CommandBoundaryServer(const CommandBoundaryServer&) = delete;
    CommandBoundaryServer& operator=(const CommandBoundaryServer&) = delete;
    
    // Server lifecycle
    CommandBoundaryResult start();
    void stop();
    
    // Configuration
    CommandBoundaryServer& set_max_connections(size_t max);
    CommandBoundaryServer& set_timeout(std::chrono::milliseconds timeout);
    CommandBoundaryServer& set_execution_callback(ExecutionCallback cb);
    
    // Block until server stops (for main thread)
    void run_until_stopped();
    
    // Check if running
    bool is_running() const { return running_.load(); }
    
    // Get the socket path
    const std::filesystem::path& socket_path() const { return socket_path_; }

private:
    std::filesystem::path socket_path_;
    environment::ipc::UnixDomainSocket socket_;
    
    std::atomic<bool> running_{false};
    std::thread accept_thread_;
    
    size_t max_connections_{10};
    std::chrono::milliseconds timeout_ms_{30000};  // Default 30 seconds
    
    ExecutionCallback execution_callback_;
    
    // Accept incoming connection and handle it
    void accept_loop();
    
    // Handle a single client connection
    void handle_client(int client_fd);
    
    // Authenticate peer based on credentials
    PeerIdentity authenticate_peer(int client_fd) const;
    
    // Parse command message from stream
    CommandMessage parse_command_message(int fd);
    
    // Serialize and send response
    bool send_response(int fd, const CommandResponse& resp);
};

// ============================================================================
// CommandBoundaryClient — IPC command boundary client
//
// Connects to a command boundary server and sends typed command messages.
// ============================================================================

class CommandBoundaryClient {
public:
    explicit CommandBoundaryClient(std::filesystem::path socket_path);
    
    ~CommandBoundaryClient();
    
    // Move semantics only
    CommandBoundaryClient(CommandBoundaryClient&&) noexcept;
    CommandBoundaryClient& operator=(CommandBoundaryClient&&) noexcept;
    
    // Delete copy semantics
    CommandBoundaryClient(const CommandBoundaryClient&) = delete;
    CommandBoundaryClient& operator=(const CommandBoundaryClient&) = delete;
    
    // Connection management
    CommandBoundaryResult connect(std::chrono::milliseconds timeout = std::chrono::seconds(5));
    void disconnect();
    
    bool is_connected() const { return connected_.load(); }
    
    // Send command and wait for response
    CommandBoundaryResult send_command(
        const command::CommandIntent& intent,
        CommandResponse* out_response,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    );
    
    // Send command without waiting for response (fire-and-forget)
    CommandBoundaryResult send_command_async(const command::CommandIntent& intent);

private:
    std::filesystem::path socket_path_;
    int socket_fd_{-1};
    
    std::atomic<bool> connected_{false};
    
    // Connection timeout handling
    CommandBoundaryResult connect_with_timeout(std::chrono::milliseconds timeout);
    
    // Send raw data with timeout
    ssize_t send_with_timeout(const void* data, size_t len, std::chrono::milliseconds timeout);
    
    // Receive raw data with timeout
    ssize_t recv_with_timeout(void* buffer, size_t len, std::chrono::milliseconds timeout);
};

// ============================================================================
// Utility Functions
// ============================================================================

// Get the session-scoped IPC directory for command boundary sockets
std::filesystem::path get_command_boundary_socket_dir(
    const environment::sessions::RuntimeDirectoryInfo& rt_info);

// Create a typed CommandIntent from high-level operation request
CommandMessage make_command_message_from_operation(
    const core::OperationRequest& op_request,
    std::string caller_id = {});

}  // namespace ipc
}  // namespace rebuntu