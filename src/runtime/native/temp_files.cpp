// rebuntu::environment::temp_files — Secure Temporary Files Implementation (Phase 2.12)
#include <observation/environment/temp_files.hpp>

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <chrono>
#include <random>

namespace rebuntu::environment::temp_files {

// ============================================================================
// SecureTempFile implementation
// ============================================================================

SecureTempFile::SecureTempFile(int fd, const std::filesystem::path& path, mode_t permissions)
    : fd_(fd), path_(path), permissions_(permissions), removed_(false) {
}

SecureTempFile::~SecureTempFile() {
    remove();
}

SecureTempFile::SecureTempFile(SecureTempFile&& other) noexcept
    : fd_(other.fd_), path_(std::move(other.path_)), 
      permissions_(other.permissions_), removed_(other.removed_) {
    other.fd_ = -1;
    other.removed_ = true;
}

SecureTempFile& SecureTempFile::operator=(SecureTempFile&& other) noexcept {
    if (this != &other) {
        remove();  // Clean up this file first
        fd_ = other.fd_;
        path_ = std::move(other.path_);
        permissions_ = other.permissions_;
        removed_ = other.removed_;
        other.fd_ = -1;
        other.removed_ = true;
    }
    return *this;
}

void SecureTempFile::remove() {
    if (fd_ >= 0 && !removed_) {
        // Try to unlink the file
        std::error_code ec;
        std::filesystem::remove(path_, ec);
        removed_ = true;
    }
}

size_t SecureTempFile::write(const void* data, size_t size) {
    if (fd_ < 0) {
        return 0;
    }
    
    ssize_t result = ::write(fd_, data, size);
    if (result < 0) {
        return 0;
    }
    return static_cast<size_t>(result);
}

int SecureTempFile::release_fd() {
    int fd = fd_;
    fd_ = -1;
    return fd;
}

// ============================================================================
// SecureTempDir implementation
// ============================================================================

SecureTempDir::SecureTempDir(const std::filesystem::path& path, mode_t permissions)
    : path_(path), permissions_(permissions), removed_(false) {
}

SecureTempDir::~SecureTempDir() {
    remove();
}

SecureTempDir::SecureTempDir(SecureTempDir&& other) noexcept
    : path_(std::move(other.path_)), permissions_(other.permissions_), removed_(other.removed_) {
    other.removed_ = true;
}

SecureTempDir& SecureTempDir::operator=(SecureTempDir&& other) noexcept {
    if (this != &other) {
        remove();  // Clean up this dir first
        path_ = std::move(other.path_);
        permissions_ = other.permissions_;
        removed_ = other.removed_;
        other.removed_ = true;
    }
    return *this;
}

void SecureTempDir::remove() {
    if (!path_.empty() && !removed_) {
        std::error_code ec;
        std::filesystem::remove_all(path_, ec);
        removed_ = true;
    }
}

TempFileResult SecureTempDir::create_file(const std::string& name, mode_t permissions) {
    auto file_path = path_ / name;
    return SecureTempFile::create_in_directory(file_path.parent_path(), name, permissions);
}

// ============================================================================
// Utility Functions
// ============================================================================

std::filesystem::path get_runtime_tmp_dir(const sessions::RuntimeDirectoryInfo& rt_info) {
    if (rt_info.status == sessions::RuntimeDirStatus::kAvailable) {
        return rt_info.path / "tmp";
    }
    return std::filesystem::path();
}

std::filesystem::path get_system_temp_dir() {
    // Prefer $TMPDIR, then /tmp
    const char* tmpdir = std::getenv("TMPDIR");
    if (tmpdir && std::string(tmpdir).length() > 0) {
        return std::filesystem::path(tmpdir);
    }
    return "/tmp";
}

std::string generate_unique_name(const std::string& prefix) {
    // Generate a unique name using timestamp + random
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();
    
    // Simple random generator (not cryptographically secure, but sufficient for temp names)
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 61);
    
    static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    std::string suffix;
    for (int i = 0; i < 8; ++i) {
        suffix += chars[dis(gen)];
    }
    
    return prefix + std::to_string(microseconds) + "-" + suffix;
}

bool is_safe_temp_directory(const std::filesystem::path& dir) {
    if (dir.empty()) {
        return false;
    }
    
    std::error_code ec;
    if (!std::filesystem::exists(dir, ec)) {
        return false;
    }
    
    if (!std::filesystem::is_directory(dir, ec)) {
        return false;
    }
    
    // Check that it's world-writable (typical for temp directories)
    struct stat st;
    if (stat(dir.string().c_str(), &st) == 0) {
        // Should be writable by owner at minimum
        if (!(st.st_mode & (S_IWUSR | S_IWGRP | S_IWOTH))) {
            return false;
        }
    }
    
    return true;
}

// ============================================================================
// SecureTempFile static methods
// ============================================================================

TempFileResult SecureTempFile::create_in_directory(
    const std::filesystem::path& dir,
    const std::string& prefix,
    mode_t permissions) {
    
    TempFileResult result;
    result.path = dir;
    
    if (dir.empty()) {
        result.status = TempFileStatus::kInvalidPath;
        result.error_message = "empty directory path";
        return result;
    }
    
    // Check directory exists and is safe
    std::error_code ec;
    if (!std::filesystem::exists(dir, ec)) {
        // Try to create it
        if (!std::filesystem::create_directories(dir, ec)) {
            result.status = TempFileStatus::kSystemError;
            result.error_message = "failed to create directory: " + ec.message();
            return result;
        }
    } else if (!std::filesystem::is_directory(dir, ec)) {
        result.status = TempFileStatus::kInvalidPath;
        result.error_message = "path exists but is not a directory";
        return result;
    }
    
    // Generate unique name and try to create the file
    for (int attempt = 0; attempt < 100; ++attempt) {
        std::string name = generate_unique_name(prefix);
        auto path = dir / name;
        
        // Use O_CREAT | O_EXCL for atomic creation
        int fd = ::open(
            path.string().c_str(),
            O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC,
            permissions
        );
        
        if (fd >= 0) {
            // Successfully created the file
            result.fd = fd;
            result.path = path;
            result.status = TempFileStatus::kSuccess;
            return result;
        }
        
        if (errno != EEXIST) {
            // Unexpected error
            break;
        }
        // File exists, try again with different name
    }
    
    result.status = TempFileStatus::kSystemError;
    result.error_message = "failed to create temporary file after multiple attempts: " + std::string(std::strerror(errno));
    return result;
}

TempFileResult SecureTempFile::create_in_runtime_tmp(const sessions::RuntimeDirectoryInfo& rt_info) {
    auto tmp_dir = get_runtime_tmp_dir(rt_info);
    
    if (!tmp_dir.empty()) {
        return create_in_directory(tmp_dir, "rebuntu-", 0600);
    }
    
    // Fallback to system temp
    TempFileResult result;
    result.status = TempFileStatus::kSystemError;
    result.error_message = "runtime tmp directory unavailable";
    return result;
}

TempFileResult SecureTempFile::create_in_system_temp(
    const std::string& prefix,
    mode_t permissions) {
    
    auto temp_dir = get_system_temp_dir();
    return create_in_directory(temp_dir, prefix, permissions);
}

}  // namespace rebuntu::environment::temp_files