// rebuntu::environment::locks — Locking Primitives Implementation (Phase 2.13)
//
// This implements Rebuntu's canonical locking mechanisms:
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

#include <observation/environment/locks.hpp>

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <poll.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace rebuntu::environment::locks {

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

// ============================================================================
// FileLock implementation
// ============================================================================

FileLock::FileLock(int fd, const std::filesystem::path& path)
    : fd_(fd), path_(path), locked_(false) {
}

FileLock::~FileLock() {
    release();
}

FileLock::FileLock(FileLock&& other) noexcept
    : fd_(other.fd_), path_(std::move(other.path_)), locked_(other.locked_) {
    other.fd_ = -1;
    other.locked_ = false;
}

FileLock& FileLock::operator=(FileLock&& other) noexcept {
    if (this != &other) {
        release();  // Release this lock first
        fd_ = other.fd_;
        path_ = std::move(other.path_);
        locked_ = other.locked_;
        other.fd_ = -1;
        other.locked_ = false;
    }
    return *this;
}

LockResult FileLock::open(const std::filesystem::path& path) {
    LockResult result;
    result.path = path;
    
    if (path.empty()) {
        result.status = LockStatus::kInvalidPath;
        result.error_message = "empty path";
        return result;
    }
    
    // Check for symlinks in parent path (security concern - TOCTOU prevention)
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            result.status = LockStatus::kInvalidPath;
            result.error_message = "path contains symlinks which may be a security risk";
            return result;
        }
        parent = parent.parent_path();
    }
    
    // Check if the target file itself is a symlink (symlink attacks)
    struct stat lstat_buf;
    if (lstat(path.c_str(), &lstat_buf) == 0) {
        if (S_ISLNK(lstat_buf.st_mode)) {
            result.status = LockStatus::kInvalidPath;
            result.error_message = "target path is a symlink which may be a security risk";
            return result;
        }
    } else if (errno != ENOENT) {
        // If stat fails with something other than "file not found", report error
        result.status = LockStatus::kSystemError;
        result.error_message = "failed to check file: " + errno_string(errno);
        return result;
    }
    
    // Open the file (create if it doesn't exist) - no O_NOFOLLOW as we want to create
    int fd = ::open(path.c_str(), O_RDWR | O_CREAT, 0600);
    if (fd < 0) {
        result.status = LockStatus::kSystemError;
        result.error_message = "failed to open lock file: " + errno_string(errno);
        return result;
    }
    
    result.fd = fd;
    result.status = LockStatus::kSuccess;
    return result;
}

LockResult FileLock::try_acquire(const LockOptions& options) {
    LockResult result;
    result.path = path_;
    result.fd = fd_;
    
    if (fd_ < 0) {
        result.status = LockStatus::kSystemError;
        result.error_message = "invalid file descriptor";
        return result;
    }
    
    // Determine lock type
    int lock_flags = LOCK_EX;  // Exclusive lock
    
    if (options.mode == LockMode::kNonBlocking) {
        lock_flags |= LOCK_NB;
    }
    
    // For timeout mode, use poll to wait with timeout
    if (options.mode == LockMode::kTimeout && options.timeout.has_value()) {
        auto start_time = std::chrono::steady_clock::now();
        
        while (true) {
            if (::flock(fd_, lock_flags & ~LOCK_NB) == 0) {
                // Got the lock
                locked_ = true;
                result.status = LockStatus::kSuccess;
                return result;
            }
            
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                result.status = LockStatus::kSystemError;
                result.error_message = "flock failed: " + errno_string(errno);
                return result;
            }
            
            // Check timeout - elapsed is in milliseconds
            auto elapsed = std::chrono::steady_clock::now() - start_time;
            int64_t elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            if (elapsed_ms >= options.timeout.value().count()) {
                result.status = LockStatus::kTimeout;
                result.error_message = "timed out waiting for lock";
                return result;
            }
            
            // Wait a bit before retrying
            struct pollfd pfd = {fd_, POLLIN, 0};
            int64_t timeout_ms = options.timeout.value().count();
            int64_t remaining_ms = timeout_ms - elapsed_ms;
            int wait_ms = std::min(100, static_cast<int>(remaining_ms));
            if (wait_ms > 0) {
                poll(&pfd, 1, wait_ms);
            }
        }
    }
    
    // Direct flock call
    if (::flock(fd_, lock_flags) == 0) {
        locked_ = true;
        result.status = LockStatus::kSuccess;
    } else {
        if (options.mode == LockMode::kNonBlocking && 
            (errno == EWOULDBLOCK || errno == EAGAIN)) {
            result.status = LockStatus::kWouldBlock;
        } else {
            result.status = LockStatus::kSystemError;
        }
        result.error_message = "flock failed: " + errno_string(errno);
    }
    
    return result;
}

void FileLock::release() {
    if (fd_ >= 0 && locked_) {
        ::flock(fd_, LOCK_UN);
        locked_ = false;
    }
    // Note: We don't close the fd - caller may want to reuse it
}

// ============================================================================
// Utility Functions
// ============================================================================

LockResult create_lock_file(const std::filesystem::path& path) {
    LockResult result;
    result.path = path;
    
    if (path.empty()) {
        result.status = LockStatus::kInvalidPath;
        result.error_message = "empty path";
        return result;
    }
    
    // Check for symlinks in parent path
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent)) {
            result.status = LockStatus::kInvalidPath;
            result.error_message = "path contains symlinks which may be a security risk";
            return result;
        }
        parent = parent.parent_path();
    }
    
    // Open/create the file
    int fd = ::open(path.c_str(), O_RDWR | O_CREAT, 0600);
    if (fd < 0) {
        result.status = LockStatus::kSystemError;
        result.error_message = "failed to create lock file: " + errno_string(errno);
        return result;
    }
    
    result.fd = fd;
    result.status = LockStatus::kSuccess;
    return result;
}

bool is_safe_lock_path(const std::filesystem::path& path) {
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
    
    // Check file permissions - should not be world-writable
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        mode_t actual_mode = st.st_mode & 0777;
        return !(actual_mode & 0002);  // Not world-writable
    }
    
    // If we can't stat, assume it might be safe (will fail at use)
    return true;
}

std::optional<pid_t> get_lock_holder_pid(const std::filesystem::path& path) {
    if (path.empty()) {
        return std::nullopt;
    }
    
    // Check for symlinks
    if (std::filesystem::is_symlink(path)) {
        return std::nullopt;
    }
    
    // Try to read /proc/locks to find lock holders
    std::ifstream locks_file("/proc/locks");
    if (!locks_file.is_open()) {
        return std::nullopt;
    }
    
    // Note: This is a simplified implementation. In production,
    // you might use fcntl F_GETLK or check /proc/*/fd for actual lock holders
    
    // For now, we return nullopt since there's no reliable way to determine
    // the PID of the process holding an flock without tracking it ourselves
    // or using fcntl with record locking (which tracks PIDs)
    
    return std::nullopt;
}

}  // namespace rebuntu::environment::locks