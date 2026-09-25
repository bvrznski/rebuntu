// rebuntu::environment::locks — Locking Primitives (Phase 2.12)
//
// This establishes Rebuntu's canonical locking mechanisms:
//
//   LOCKING MECHANISMS
//     - flock/fcntl for kernel-mediated locks
//     - Advisory vs mandatory locking semantics
//     - Blocking/non-blocking acquisition with timeout/cancellation
//     - Lock ownership tracked by kernel (not file existence)
//
//   CRITICAL INVARIENTS
//     - File existence != lock ownership
//     - Kernel-mediated ownership (flock/fcntl)
//     - Stale locks handled via process termination detection
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/locks.hpp
//
// Phase 2.12 extends Phase 2.9 (directories):
// - Flock-based locking with kernel-mediated ownership
// - Non-blocking acquisition with timeout support
// - Automatic lock release on process termination

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <chrono>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <string>
#include <string_view>
#include <optional>
#include <filesystem>

#include <observation/environment/scope.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::environment::locks {

// ============================================================================
// LockStatus - Result of lock operations
// ============================================================================

enum class LockStatus {
    kSuccess,           // Lock acquired successfully
    kWouldBlock,        // Would block (non-blocking mode)
    kTimeout,           // Timeout waiting for lock
    kPermissionDenied,  // Cannot access lock file
    kInvalidPath,       // Invalid or unsafe path
    kSystemError,       // System call failed (errno available)
    kUnknown,           // Unknown error
};

struct LockResult {
    LockStatus status = LockStatus::kUnknown;
    std::filesystem::path path;
    int fd = -1;  // File descriptor (valid >= 0)
    std::optional<std::string> error_message;
    
    core::SemanticStatus semantic_status() const {
        switch (status) {
            case LockStatus::kSuccess:
                return core::SemanticStatus::kSuccess;
            case LockStatus::kWouldBlock:
            case LockStatus::kTimeout:
            case LockStatus::kPermissionDenied:
            case LockStatus::kInvalidPath:
                return core::SemanticStatus::kFailure;
            case LockStatus::kSystemError:
                return core::SemanticStatus::kUnknown;
        }
        return core::SemanticStatus::kUnknown;
    }
    
    bool is_success() const {
        return semantic_status() == core::SemanticStatus::kSuccess;
    }
};

// ============================================================================
// LockMode - Blocking/non-blocking modes
// ============================================================================

enum class LockMode {
    kBlocking,      // Wait indefinitely for lock
    kNonBlocking,   // Return immediately if lock unavailable
    kTimeout,       // Wait up to a timeout period
};

struct LockOptions {
    LockMode mode = LockMode::kNonBlocking;
    std::optional<std::chrono::milliseconds> timeout;
    
    static LockOptions blocking() { return {LockMode::kBlocking, std::nullopt}; }
    static LockOptions non_blocking() { return {LockMode::kNonBlocking, std::nullopt}; }
    static LockOptions with_timeout(std::chrono::milliseconds ms) {
        return {LockMode::kTimeout, ms};
    }
};

// ============================================================================
// SharedLock/ExclusiveLock - RAII wrappers for lock types
// ============================================================================

class FileLock {
public:
    // Open a lock file and create an uninitialized lock object
    static LockResult open(const std::filesystem::path& path);
    
    // Attempt to acquire the lock with given options
    LockResult try_acquire(const LockOptions& options = LockOptions::non_blocking());
    
    // Release the lock (called by destructor)
    void release();
    
    // Check if this lock is currently held
    bool is_held() const { return fd_ >= 0 && locked_; }
    
    // Get the file descriptor (for polling/select)
    int fd() const { return fd_; }
    
    // Constructor - takes ownership of already-acquired lock
    FileLock(int fd, const std::filesystem::path& path);
    
    // Destructor - releases lock on destruction
    ~FileLock();
    
    // Move semantics
    FileLock(FileLock&& other) noexcept;
    FileLock& operator=(FileLock&& other) noexcept;
    
    // Delete copy semantics (locks are not copyable)
    FileLock(const FileLock&) = delete;
    FileLock& operator=(const FileLock&) = delete;

private:
    int fd_;
    std::filesystem::path path_;
    bool locked_;
};

// ============================================================================
// Utility Functions
// ============================================================================

// Create a lock file at the specified path (without acquiring the lock)
LockResult create_lock_file(const std::filesystem::path& path);

// Check if a path is safe for locking (no symlinks in parent path)
bool is_safe_lock_path(const std::filesystem::path& path);

// Get the PID of the process holding the lock on a file
std::optional<pid_t> get_lock_holder_pid(const std::filesystem::path& path);

}  // namespace rebuntu::environment::locks