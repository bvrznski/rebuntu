// rebuntu::environment::temp_files — Secure Temporary Files (Phase 2.12)
//
// This establishes Rebuntu's canonical temporary file handling:
//
//   SECURE TEMPORARY FILES
//     - OS primitives: mkstemp, mkostemp, memfd_create (Linux)
//     - XDG_RUNTIME_DIR/tmp for session-scoped temps
//     - System temp directories with unique names only
//     - Automatic cleanup on destruction
//
//   CRITICAL INVARIENTS
//     - Predictable /tmp names are NEVER used (security risk)
//     - File existence != lock ownership
//     - Cleanup must happen deterministically (RAII)
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/temp_files.hpp
//
// Phase 2.12 extends Phase 2.9 (directories) and Phase 2.8 (sessions):
// - Secure temp file creation with kernel-mediated uniqueness
// - Automatic cleanup on destruction (RAII)
// - XDG_RUNTIME_DIR/tmp integration for session-scoped temps

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <filesystem>

#include <system/environment/scope.hpp>
#include <system/environment/sessions.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::environment::temp_files {

// ============================================================================
// TempFileStatus - Result of temp file operations
// ============================================================================

enum class TempFileStatus {
    kSuccess,           // Operation succeeded
    kAlreadyExists,     // Temporary name collision (extremely unlikely)
    kPermissionDenied,  // Cannot create in target directory
    kInvalidPath,       // Invalid or unsafe path
    kSystemError,       // System call failed (errno available)
    kUnknown,           // Unknown error
};

struct TempFileResult {
    TempFileStatus status = TempFileStatus::kUnknown;
    std::filesystem::path path;
    int fd = -1;  // File descriptor (valid >= 0)
    std::optional<std::string> error_message;
    
    core::SemanticStatus semantic_status() const {
        switch (status) {
            case TempFileStatus::kSuccess:
                return core::SemanticStatus::kSuccess;
            case TempFileStatus::kAlreadyExists:
            case TempFileStatus::kPermissionDenied:
            case TempFileStatus::kInvalidPath:
                return core::SemanticStatus::kFailure;
            case TempFileStatus::kSystemError:
                return core::SemanticStatus::kUnknown;
        }
        return core::SemanticStatus::kUnknown;
    }
    
    bool is_success() const {
        return semantic_status() == core::SemanticStatus::kSuccess;
    }
};

// ============================================================================
// SecureTempFile - RAII wrapper for secure temporary files
// ============================================================================

class SecureTempFile {
public:
    // Create a secure temp file in the specified directory
    static TempFileResult create_in_directory(
        const std::filesystem::path& dir,
        const std::string& prefix = "rebuntu-",
        mode_t permissions = 0600);
    
    // Create a secure temp file in session runtime tmp directory
    static TempFileResult create_in_runtime_tmp(const sessions::RuntimeDirectoryInfo& rt_info);
    
    // Create a secure temp file in system temp directory (/tmp)
    // WARNING: Only use when XDG_RUNTIME_DIR is unavailable
    static TempFileResult create_in_system_temp(
        const std::string& prefix = "rebuntu-",
        mode_t permissions = 0600);
    
    // Constructor (takes ownership of fd and path)
    SecureTempFile(int fd, const std::filesystem::path& path, mode_t permissions = 0600);
    
    // Destructor - removes the file on destruction
    ~SecureTempFile();
    
    // Move semantics
    SecureTempFile(SecureTempFile&& other) noexcept;
    SecureTempFile& operator=(SecureTempFile&& other) noexcept;
    
    // Delete copy semantics
    SecureTempFile(const SecureTempFile&) = delete;
    SecureTempFile& operator=(const SecureTempFile&) = delete;
    
    // Getters
    int fd() const { return fd_; }
    const std::filesystem::path& path() const { return path_; }
    bool is_valid() const { return fd_ >= 0; }
    bool is_removed() const { return removed_; }
    
    // Explicit removal (called by destructor)
    void remove();
    
    // Write to the temp file
    size_t write(const void* data, size_t size);
    
    // Close the file descriptor without removing the file
    // Use with caution - caller becomes responsible for cleanup
    int release_fd();

private:
    int fd_;
    std::filesystem::path path_;
    mode_t permissions_;
    bool removed_;
};

// ============================================================================
// TempDirectory - RAII wrapper for secure temporary directories
// ============================================================================

class SecureTempDir {
public:
    // Create a secure temp directory in the specified parent
    static TempFileResult create_in_directory(
        const std::filesystem::path& parent,
        const std::string& prefix = "rebuntu-",
        mode_t permissions = 0700);
    
    // Create in XDG_RUNTIME_DIR/tmp if available, system temp otherwise
    static TempFileResult create_in_runtime_or_system_tmp(
        const sessions::RuntimeDirectoryInfo& rt_info,
        const std::string& prefix = "rebuntu-");
    
    // Constructor (takes ownership of path)
    SecureTempDir(const std::filesystem::path& path, mode_t permissions = 0700);
    
    // Destructor - removes the directory on destruction
    ~SecureTempDir();
    
    // Move semantics
    SecureTempDir(SecureTempDir&& other) noexcept;
    SecureTempDir& operator=(SecureTempDir&& other) noexcept;
    
    // Delete copy semantics
    SecureTempDir(const SecureTempDir&) = delete;
    SecureTempDir& operator=(const SecureTempDir&) = delete;
    
    // Getters
    const std::filesystem::path& path() const { return path_; }
    bool is_valid() const { return !path_.empty(); }
    bool is_removed() const { return removed_; }
    
    // Explicit removal (called by destructor)
    void remove();
    
    // Create a file inside this directory
    TempFileResult create_file(const std::string& name, mode_t permissions = 0600);

private:
    std::filesystem::path path_;
    mode_t permissions_;
    bool removed_;
};

// ============================================================================
// Utility Functions
// ============================================================================

// Get the XDG_RUNTIME_DIR/tmp subdirectory for session-scoped temp files
std::filesystem::path get_runtime_tmp_dir(const sessions::RuntimeDirectoryInfo& rt_info);

// Get the system temporary directory path
std::filesystem::path get_system_temp_dir();

// Generate a unique filename with the given prefix
std::string generate_unique_name(const std::string& prefix);

// Check if a directory is safe for temp file creation (proper permissions)
bool is_safe_temp_directory(const std::filesystem::path& dir);

}  // namespace rebuntu::environment::temp_files