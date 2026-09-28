// Rebuntu Path Safety Library (Phase 6.59)
//
// Path safety auditing for filesystem operations.
// Validates path semantics, symlink behavior, ownership and TOCTOU risk
// according to the operation.
//
// Core principles:
//   * PATH SAFETY != AUTHORITY - validation prevents unsafe paths, not access control
//   * ATOMIC OPERATIONS != SAFE PATHS - atomicity doesn't prevent malicious targets
//   * CANONICALIZATION ≠ TRUST - resolved path must still be validated
//
// Architecture:
//   PathSafetyAudit → OperationContext → ValidatePath → CheckSymlinks → VerifyOwnership
//
// Key safety features:
//   - Symlink following detection and restriction
//   - Path traversal detection (.. escaping boundaries)
//   - TOCTOU mitigation via atomic operations
//   - Ownership verification for file targets
//   - Safe path canonicalization without trust assumptions

#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::path_safety {

// For optional type - use std::nullopt from <optional>

// ============================================================================
// PathSafetyResult - Result of a path safety audit
// ============================================================================

enum class SafetyCheckStatus {
    kPassed,        // Check passed, no issues found
    kWarning,       // Minor issue but operation may proceed with caution
    kFailed,        // Critical security issue, operation must be rejected
};

struct SafetyCheckResult {
    SafetyCheckStatus status = SafetyCheckStatus::kPassed;
    std::optional<std::string> reason;  // Human-readable explanation if failed
    
    static SafetyCheckResult passed() {
        SafetyCheckResult r;
        r.status = SafetyCheckStatus::kPassed;
        r.reason = std::nullopt;
        return r;
    }
    
    static SafetyCheckResult warning(std::string msg) {
        SafetyCheckResult r;
        r.status = SafetyCheckStatus::kWarning;
        r.reason = std::move(msg);
        return r;
    }
    
    static SafetyCheckResult failed(std::string msg) {
        SafetyCheckResult r;
        r.status = SafetyCheckStatus::kFailed;
        r.reason = std::move(msg);
        return r;
    }
};

// ============================================================================
// SymlinkPolicy - Controls how symlinks are handled
// ============================================================================

enum class SymlinkBehavior {
    kFollow,           // Allow following symlinks (default for read-only)
    kReject,           // Reject if path is a symlink
    kTrustedOnly,      // Follow only if all components are owned by trusted user
    kAllowButAudit,    // Allow but record symlink in audit trail
};

struct SymlinkPolicy {
    SymlinkBehavior behavior = SymlinkBehavior::kFollow;
    
    // When kTrustedOnly is set, these UIDs are considered trusted
    std::vector<uid_t> trusted_uids;
    
    bool should_audit() const {
        return behavior == SymlinkBehavior::kAllowButAudit ||
               behavior == SymlinkBehavior::kTrustedOnly;
    }
};

// ============================================================================
// PathContext - Context for path validation
// ============================================================================

enum class OperationType {
    kRead,             // Reading file content (copy source, config read)
    kWrite,            // Writing file content (copy dest, file modification)
    kCreate,           // Creating new file/directory
    kDelete,           // Deleting file/directory
    kMetadata,         // Modifying metadata (permissions, ownership)
};

enum class PathBoundary {
    kNone,             // No boundary restrictions
    kUserHome,         // Restricted to user home directory
    kSystemConfig,     // Restricted to system config directories
    kSystemData,       // Restricted to system data directories
    kTempDir,          // Restricted to temp directories
    kCustom,           // Custom boundary path specified
};

struct PathContext {
    OperationType op_type = OperationType::kRead;
    std::optional<uid_t> target_owner_uid;  // Expected owner of target
    
    // Boundary restrictions
    PathBoundary boundary = PathBoundary::kNone;
    std::optional<std::filesystem::path> custom_boundary;
    
    // Symlink handling
    SymlinkPolicy symlink_policy;
    
    // Additional context for audit trail
    bool require_audit_trail = false;
};

// ============================================================================
// Path Safety Validation Functions
// ============================================================================

// Validate that a path doesn't contain path traversal sequences
SafetyCheckResult validate_path_syntax(const std::filesystem::path& path);

// Check if path is under a specified boundary directory
SafetyCheckResult validate_path_in_boundary(
    const std::filesystem::path& path,
    const std::filesystem::path& boundary,
    bool allow_boundary_as_target = true);

// Check for symlink following and apply policy
SafetyCheckResult check_symlink_policy(
    const std::filesystem::path& path,
    const SymlinkPolicy& policy,
    std::error_code* ec = nullptr);

// Verify file ownership matches expected owner
SafetyCheckResult verify_ownership(
    const std::filesystem::path& path,
    uid_t expected_uid,
    bool allow_dir = false);

// Validate path for a specific operation type with given context
SafetyCheckResult validate_path_for_operation(
    const std::filesystem::path& path,
    const PathContext& context,
    std::error_code* ec = nullptr);

// ============================================================================
// TOCTOU Mitigation Utilities
// ============================================================================

// File descriptor wrapper that holds open file descriptor
class FileDescriptor {
public:
    FileDescriptor() = default;
    explicit FileDescriptor(int fd);
    ~FileDescriptor();
    
    // Move only
    FileDescriptor(FileDescriptor&& other) noexcept;
    FileDescriptor& operator=(FileDescriptor&& other) noexcept;
    
    // Delete copy operations
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;
    
    int get() const { return fd_; }
    bool is_valid() const { return fd_ >= 0; }
    void close();
    
private:
    int fd_{-1};
};

// Open a file descriptor atomically and validate path
std::optional<FileDescriptor> open_file_safely(
    const std::filesystem::path& path,
    int flags,
    mode_t mode = 0644);

// Verify file identity using fstat to prevent TOCTOU
struct FileIdentity {
    dev_t device_id;
    ino_t inode_number;
    uid_t owner_uid;
    gid_t group_gid;
    off_t size;
};

std::optional<FileIdentity> get_file_identity(int fd);
std::optional<FileIdentity> get_file_identity(const std::filesystem::path& path);

// ============================================================================
// Safe Path Canonicalization
// ============================================================================

// Resolve paths without trust assumptions
// Returns the resolved path with symlink information for audit
struct ResolvedPath {
    std::filesystem::path canonical_path;
    std::vector<std::filesystem::path> symlinks_resolved;  // In order from source to target
    bool all_components_regular = true;  // No unexpected special files
};

std::optional<ResolvedPath> safe_canonicalize(
    const std::filesystem::path& path,
    const SymlinkPolicy& policy,
    size_t max_depth = 20);

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorPathTraversal[] = "E_PATH_TRAVERSAL";
inline constexpr char kErrorSymlinkForbidden[] = "E_SYMLINK_FORBIDDEN";
inline constexpr char kErrorOwnershipMismatch[] = "E_OWNERSHIP_MISMATCH";
inline constexpr char kErrorInvalidPathSyntax[] = "E_INVALID_PATH_SYNTAX";
inline constexpr char kErrorBoundaryViolation[] = "E_BOUNDARY_VIOLATION";

}  // namespace rebuntu::path_safety