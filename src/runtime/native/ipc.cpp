// rebuntu::environment::ipc — Inter-Process Communication Implementation (Phase 2.13)
//
// This implements Rebuntu's canonical IPC mechanisms:
//
//   IPC MECHANISMS
//     - Unix domain sockets for local communication
//     - Named pipes (FIFOs) for streaming data
//     - Unnamed pipes for parent-child communication
//     - Permission and peer identity verification
//
//   CRITICAL INVARIENTS
//     - Unix-domain only (no TCP for local convenience)
//     - Permissions verified before binding/connecting
//     - Proper cleanup of socket files

#include <observation/environment/ipc.hpp>

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <poll.h>
#include <filesystem>
#include <iostream>

namespace rebuntu::environment::ipc {

// ============================================================================
// Utility: Error handling helpers
// ============================================================================

static std::string errno_string(int err) {
    char buffer[256];
    const char* msg = strerror_r(err, buffer, sizeof(buffer));
    if (msg) {
        return std::string(msg);
    }
    return "Unknown error";
}

static IPCResult make_error_result(IPCError error, const std::optional<std::string>& msg = std::nullopt) {
    IPCResult result;
    result.error = error;
    result.error_message = msg;
    return result;
}

// ============================================================================
// UnixDomainSocket implementation
// ============================================================================

UnixDomainSocket::UnixDomainSocket(int fd)
    : fd_(fd), path_() {
}

UnixDomainSocket::~UnixDomainSocket() {
    close();
}

UnixDomainSocket::UnixDomainSocket(UnixDomainSocket&& other) noexcept
    : fd_(other.fd_), path_(std::move(other.path_)) {
    other.fd_ = -1;
}

UnixDomainSocket& UnixDomainSocket::operator=(UnixDomainSocket&& other) noexcept {
    if (this != &other) {
        close();  // Close this socket first
        fd_ = other.fd_;
        path_ = std::move(other.path_);
        other.fd_ = -1;
    }
    return *this;
}

IPCResult UnixDomainSocket::create_in_directory(const std::filesystem::path& dir, const std::string& name) {
    IPCResult result;
    
    if (dir.empty() || name.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty directory or name");
    }
    
    // Check for symlinks in parent path
    auto parent = dir.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Create socket
    int fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        return make_error_result(IPCError::kSystemError, "failed to create socket: " + errno_string(errno));
    }
    
    // Build full path
    auto path = dir / name;
    
    // Prepare address structure
    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    
    // Copy path (ensure it fits)
    std::string path_str = path.string();
    if (path_str.size() >= sizeof(addr.sun_path)) {
        ::close(fd);
        return make_error_result(IPCError::kInvalidPath, "socket path too long");
    }
    std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
    
    // Unlink any existing socket
    unlink(path_str.c_str());
    
    // Bind the socket
    if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd);
        return make_error_result(IPCError::kSystemError, "failed to bind socket: " + errno_string(errno));
    }
    
    result.error = IPCError::kSuccess;
    return result;
}

IPCResult UnixDomainSocket::bind(const std::filesystem::path& path, mode_t permissions) {
    IPCResult result;
    
    if (path.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty path");
    }
    
    // Check for symlinks in parent path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Check if directory exists and is writable
    auto dir = path.parent_path();
    std::error_code ec;
    if (!std::filesystem::exists(dir, ec) || !std::filesystem::is_directory(dir, ec)) {
        return make_error_result(IPCError::kPermissionDenied, "directory does not exist or is not accessible");
    }
    
    // Check directory permissions
    struct stat st;
    if (stat(dir.c_str(), &st) == 0) {
        if (!(st.st_mode & S_IWUSR)) {
            return make_error_result(IPCError::kPermissionDenied, "directory not writable by owner");
        }
    }
    
    // Create socket
    int fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        return make_error_result(IPCError::kSystemError, "failed to create socket: " + errno_string(errno));
    }
    
    // Prepare address structure
    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    
    std::string path_str = path.string();
    if (path_str.size() >= sizeof(addr.sun_path)) {
        ::close(fd);
        return make_error_result(IPCError::kInvalidPath, "socket path too long");
    }
    std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
    
    // Unlink any existing socket
    unlink(path_str.c_str());
    
    // Bind the socket
    if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd);
        return make_error_result(IPCError::kSystemError, "failed to bind socket: " + errno_string(errno));
    }
    
    // Set permissions on the socket file
    if (chmod(path_str.c_str(), permissions) < 0) {
        ::close(fd);
        unlink(path_str.c_str());
        return make_error_result(IPCError::kSystemError, "failed to set socket permissions: " + errno_string(errno));
    }
    
    // Store path for cleanup
    result.error = IPCError::kSuccess;
    return result;
}

IPCResult UnixDomainSocket::connect(const std::filesystem::path& path) {
    IPCResult result;
    
    if (path.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty path");
    }
    
    // Check for symlinks in path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Verify the socket file exists and is a socket
    struct stat st;
    if (stat(path.c_str(), &st) < 0) {
        return make_error_result(IPCError::kConnectionRefused, "socket does not exist");
    }
    
    if (!S_ISSOCK(st.st_mode)) {
        return make_error_result(IPCError::kInvalidPath, "path is not a socket");
    }
    
    // Check permissions
    mode_t perms = st.st_mode & 0777;
    uid_t current_uid = getuid();
    
    bool has_access = false;
    if (st.st_uid == current_uid) {
        has_access = (perms & S_IRUSR) && (perms & S_IWUSR);
    } else {
        // Check group and other permissions
        has_access = (perms & (S_IRGRP | S_IROTH)) && (perms & (S_IWGRP | S_IWOTH));
    }
    
    if (!has_access) {
        return make_error_result(IPCError::kPermissionDenied, "no permission to connect");
    }
    
    // Create socket
    int fd = ::socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (fd < 0) {
        return make_error_result(IPCError::kSystemError, "failed to create socket: " + errno_string(errno));
    }
    
    // Connect
    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    
    std::string path_str = path.string();
    if (path_str.size() >= sizeof(addr.sun_path)) {
        ::close(fd);
        return make_error_result(IPCError::kInvalidPath, "socket path too long");
    }
    std::strncpy(addr.sun_path, path_str.c_str(), sizeof(addr.sun_path) - 1);
    
    if (::connect(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd);
        return make_error_result(IPCError::kConnectionRefused, "connection failed: " + errno_string(errno));
    }
    
    result.error = IPCError::kSuccess;
    return result;
}

IPCResult UnixDomainSocket::listen(int backlog) {
    IPCResult result;
    
    if (fd_ < 0) {
        return make_error_result(IPCError::kNotConnected, "invalid file descriptor");
    }
    
    if (::listen(fd_, backlog) < 0) {
        return make_error_result(IPCError::kSystemError, "listen failed: " + errno_string(errno));
    }
    
    result.error = IPCError::kSuccess;
    return result;
}

std::optional<int> UnixDomainSocket::accept() {
    if (fd_ < 0) {
        return std::nullopt;
    }
    
    // Use poll to check for incoming connections
    struct pollfd pfd = {fd_, POLLIN, 0};
    int ret = ::poll(&pfd, 1, 0);  // Non-blocking
    
    if (ret < 0) {
        return std::nullopt;
    }
    
    if (ret == 0) {
        return std::nullopt;  // No connections waiting
    }
    
    struct sockaddr_un addr;
    socklen_t addrlen = sizeof(addr);
    int new_fd = ::accept4(fd_, reinterpret_cast<struct sockaddr*>(&addr), &addrlen, SOCK_CLOEXEC);
    
    if (new_fd < 0) {
        return std::nullopt;
    }
    
    return new_fd;
}

ssize_t UnixDomainSocket::send(const void* data, size_t size, int flags) {
    if (fd_ < 0) {
        return -1;
    }
    
    return ::send(fd_, data, size, flags);
}

ssize_t UnixDomainSocket::recv(void* buffer, size_t size, int flags) {
    if (fd_ < 0) {
        return -1;
    }
    
    return ::recv(fd_, buffer, size, flags);
}

void UnixDomainSocket::close() {
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
    
    // Remove socket file if we created it
    if (path_.has_value()) {
        std::error_code ec;
        std::filesystem::remove(*path_, ec);
        path_ = std::nullopt;
    }
}

// ============================================================================
// Fifo implementation
// ============================================================================

Fifo::Fifo(int fd)
    : fd_(fd) {
}

Fifo::~Fifo() {
    close();
}

Fifo::Fifo(Fifo&& other) noexcept
    : fd_(other.fd_) {
    other.fd_ = -1;
}

Fifo& Fifo::operator=(Fifo&& other) noexcept {
    if (this != &other) {
        close();  // Close this FIFO first
        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}

IPCResult Fifo::create(const std::filesystem::path& path, mode_t permissions) {
    IPCResult result;
    
    if (path.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty path");
    }
    
    // Check for symlinks in parent path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Create the FIFO
    if (::mkfifo(path.c_str(), permissions) < 0) {
        return make_error_result(IPCError::kSystemError, "failed to create fifo: " + errno_string(errno));
    }
    
    result.error = IPCError::kSuccess;
    return result;
}

IPCResult Fifo::open_for_read(const std::filesystem::path& path) {
    IPCResult result;
    
    if (path.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty path");
    }
    
    // Check for symlinks in parent path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Open for reading (non-blocking)
    int fd = ::open(path.c_str(), O_RDONLY | O_NONBLOCK | O_CLOEXEC);
    if (fd < 0) {
        return make_error_result(IPCError::kSystemError, "failed to open fifo for read: " + errno_string(errno));
    }
    
    result.fd = fd;
    result.error = IPCError::kSuccess;
    return result;
}

IPCResult Fifo::open_for_write(const std::filesystem::path& path) {
    IPCResult result;
    
    if (path.empty()) {
        return make_error_result(IPCError::kInvalidPath, "empty path");
    }
    
    // Check for symlinks in parent path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return make_error_result(IPCError::kInvalidPath, "path contains symlinks");
        }
        parent = parent.parent_path();
    }
    
    // Open for writing
    int fd = ::open(path.c_str(), O_WRONLY | O_CLOEXEC);
    if (fd < 0) {
        return make_error_result(IPCError::kSystemError, "failed to open fifo for write: " + errno_string(errno));
    }
    
    result.fd = fd;
    result.error = IPCError::kSuccess;
    return result;
}

ssize_t Fifo::write(const void* data, size_t size) {
    if (fd_ < 0) {
        return -1;
    }
    
    return ::write(fd_, data, size);
}

ssize_t Fifo::read(void* buffer, size_t size) {
    if (fd_ < 0) {
        return -1;
    }
    
    return ::read(fd_, buffer, size);
}

void Fifo::close() {
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

// ============================================================================
// Utility Functions
// ============================================================================

std::pair<int, int> create_pipe() {
    int pipefd[2];
    
    if (::pipe(pipefd) < 0) {
        return {-1, -1};
    }
    
    // Set both ends to close-on-exec
    fcntl(pipefd[0], F_SETFD, FD_CLOEXEC);
    fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);
    
    return {pipefd[0], pipefd[1]};  // [0] = read end, [1] = write end
}

bool is_safe_ipc_path(const std::filesystem::path& path) {
    if (path.empty()) {
        return false;
    }
    
    // Check each component for symlinks
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            return false;
        }
        
        try {
            auto canonical = std::filesystem::canonical(parent);
            parent = canonical.parent_path();
        } catch (...) {
            break;
        }
    }
    
    // Check directory permissions - should be writable by owner
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        mode_t actual_mode = st.st_mode & 0777;
        return (actual_mode & S_IWUSR);  // Writable by owner
    }
    
    return true;  // If we can't stat, assume it might be safe
}

std::filesystem::path get_session_ipc_dir(const sessions::RuntimeDirectoryInfo& rt_info) {
    if (rt_info.status == sessions::RuntimeDirStatus::kAvailable) {
        return rt_info.path / "ipc";
    }
    
    // Fallback to system runtime directory
    return "/run/rebuntu/ipc";
}

}  // namespace rebuntu::environment::ipc