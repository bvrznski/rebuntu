// rebuntu::environment::ipc — Inter-Process Communication (Phase 2.12)
//
// This establishes Rebuntu's canonical IPC mechanisms:
//
//   IPC MECHANISMS
//     - Unix domain sockets for local communication
//     - Named pipes (FIFOs) for streaming data
//     - Unnamed pipes for parent-child communication
//     - D-Bus integration where appropriate
//
//   CRITICAL INVARIENTS
//     - Unix-domain only (no TCP for local convenience)
//     - Permissions and peer identity verified
//     - Proper cleanup of socket files
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/ipc.hpp
//
// Phase 2.12 extends Phase 2.9 (directories):
// - Unix domain socket creation and management
// - FIFO pipe handling
// - Permission and identity verification

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <filesystem>

#include <observation/environment/scope.hpp>
#include <observation/environment/sessions.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::environment::ipc {

// ============================================================================
// IPCError - Error codes for IPC operations
// ============================================================================

enum class IPCError {
    kSuccess,
    kWouldBlock,        // Operation would block (non-blocking mode)
    kTimeout,           // Timeout waiting for connection/data
    kPermissionDenied,  // Permission denied on socket path
    kInvalidPath,       // Invalid or unsafe path
    kSystemError,       // System call failed (errno available)
    kConnectionRefused, // Connection refused by peer
    kNotConnected,      // Not connected to a peer
};

struct IPCResult {
    IPCError error = IPCError::kSuccess;
    std::optional<std::string> error_message;
    int fd = -1;  // File descriptor (valid >= 0)
    
    core::SemanticStatus semantic_status() const {
        switch (error) {
            case IPCError::kSuccess:
                return core::SemanticStatus::kSuccess;
            case IPCError::kWouldBlock:
            case IPCError::kTimeout:
            case IPCError::kPermissionDenied:
            case IPCError::kInvalidPath:
            case IPCError::kConnectionRefused:
            case IPCError::kNotConnected:
                return core::SemanticStatus::kFailure;
            case IPCError::kSystemError:
                return core::SemanticStatus::kUnknown;
        }
        return core::SemanticStatus::kUnknown;
    }
    
    bool is_success() const {
        return semantic_status() == core::SemanticStatus::kSuccess;
    }
};

// ============================================================================
// UnixDomainSocket - RAII wrapper for Unix domain sockets
// ============================================================================

class UnixDomainSocket {
public:
    // Create a new Unix domain socket in the specified directory
    static IPCResult create_in_directory(
        const std::filesystem::path& dir,
        const std::string& name);
    
    // Bind to an existing path (for server)
    static IPCResult bind(const std::filesystem::path& path, mode_t permissions = 0666);
    
    // Connect to a socket (for client)
    static IPCResult connect(const std::filesystem::path& path);
    
    // Listen for incoming connections
    IPCResult listen(int backlog = 10);
    
    // Accept a connection
    std::optional<int> accept();
    
    // Send data
    ssize_t send(const void* data, size_t size, int flags = 0);
    
    // Receive data
    ssize_t recv(void* buffer, size_t size, int flags = 0);
    
    // Close the socket (called by destructor)
    void close();
    
    // Check if socket is valid
    bool is_valid() const { return fd_ >= 0; }
    
    // Get file descriptor
    int fd() const { return fd_; }
    
    // Constructor
    explicit UnixDomainSocket(int fd = -1);
    
    // Destructor
    ~UnixDomainSocket();
    
    // Move semantics
    UnixDomainSocket(UnixDomainSocket&& other) noexcept;
    UnixDomainSocket& operator=(UnixDomainSocket&& other) noexcept;
    
    // Delete copy semantics
    UnixDomainSocket(const UnixDomainSocket&) = delete;
    UnixDomainSocket& operator=(const UnixDomainSocket&) = delete;

private:
    int fd_;
    std::optional<std::filesystem::path> path_;
};

// ============================================================================
// FIFO - Named pipe (FIFO)
// ============================================================================

class Fifo {
public:
    // Create a named pipe
    static IPCResult create(const std::filesystem::path& path, mode_t permissions = 0666);
    
    // Open for reading
    static IPCResult open_for_read(const std::filesystem::path& path);
    
    // Open for writing
    static IPCResult open_for_write(const std::filesystem::path& path);
    
    // Write data
    ssize_t write(const void* data, size_t size);
    
    // Read data
    ssize_t read(void* buffer, size_t size);
    
    // Close the FIFO
    void close();
    
    // Check if valid
    bool is_valid() const { return fd_ >= 0; }
    
    // Get file descriptor
    int fd() const { return fd_; }
    
    explicit Fifo(int fd = -1);
    ~Fifo();
    
    // Move semantics
    Fifo(Fifo&& other) noexcept;
    Fifo& operator=(Fifo&& other) noexcept;
    
    // Delete copy semantics
    Fifo(const Fifo&) = delete;
    Fifo& operator=(const Fifo&) = delete;

private:
    int fd_;
};

// ============================================================================
// Utility Functions
// ============================================================================

// Create an unnamed pipe (for parent-child communication)
std::pair<int, int> create_pipe();

// Check if a path is safe for IPC socket creation
bool is_safe_ipc_path(const std::filesystem::path& path);

// Get the path to a session-scoped IPC socket directory
std::filesystem::path get_session_ipc_dir(const sessions::RuntimeDirectoryInfo& rt_info);

}  // namespace rebuntu::environment::ipc