// rebuntu::environment::ownership — Ownership & Permissions Contract (Phase 2.3)
//
// This establishes Rebuntu's canonical ownership and permission model:
//
//   * OWNERSHIP = Who owns an artifact (uid_t, gid_t via NSS)
//   * PERMISSIONS = What operations are allowed (mode bits, umask, ACLs)
//   * VERIFICATION = Independent postcondition observation
//   * REPAIR = Restore Rebuntu-owned artifacts to correct state
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/
//
// Phase 2.1 established identity observation.
// Phase 2.2 added group membership primitives.
// Phase 2.3 adds ownership & permission operations with verification and repair.

#pragma once

#include <observation/environment/user_identity.hpp>
#include <observation/environment/group_membership.hpp>
#include <runtime/core/contracts.hpp>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <chrono>

namespace rebuntu::environment::ownership {

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorNoSuchUser[] = "E_NO_SUCH_USER";
inline constexpr char kErrorNoSuchGroup[] = "E_NO_SUCH_GROUP";
inline constexpr char kErrorPermissionDenied[] = "E_PERMISSION_DENIED";
inline constexpr char kErrorAcquisitionFailed[] = "E_ACQUISITION_FAILED";
inline constexpr char kErrorSymlinkDetected[] = "E_SYMLINK_DETECTED";
inline constexpr char kErrorInvalidMode[] = "E_INVALID_MODE";
inline constexpr char kErrorRepairFailed[] = "E_REPAIR_FAILED";

// ============================================================================
// Permission Types
// ============================================================================

enum class PermissionType {
    kOwnerRead,      // S_IRUSR (owner read)
    kOwnerWrite,     // S_IWUSR (owner write)
    kOwnerExec,      // S_IXUSR (owner execute)
    kGroupRead,      // S_IRGRP (group read)
    kGroupWrite,     // S_IWGRP (group write)
    kGroupExec,      // S_IXGRP (group execute)
    kOtherRead,      // S_IROTH (other read)
    kOtherWrite,     // S_IWOTH (other write)
    kOtherExec,      // S_IXOTH (other execute)
    kSetuid,         // S_ISUID (set UID on execution)
    kSetgid,         // S_ISGID (set GID on execution)
    kStickyBit,      // S_ISVTX (sticky bit)
};

inline std::string_view to_string(PermissionType t) {
    switch (t) {
        case PermissionType::kOwnerRead:   return "owner-read";
        case PermissionType::kOwnerWrite:  return "owner-write";
        case PermissionType::kOwnerExec:   return "owner-execute";
        case PermissionType::kGroupRead:   return "group-read";
        case PermissionType::kGroupWrite:  return "group-write";
        case PermissionType::kGroupExec:   return "group-execute";
        case PermissionType::kOtherRead:   return "other-read";
        case PermissionType::kOtherWrite:  return "other-write";
        case PermissionType::kOtherExec:   return "other-execute";
        case PermissionType::kSetuid:      return "setuid";
        case PermissionType::kSetgid:      return "setgid";
        case PermissionType::kStickyBit:   return "sticky-bit";
    }
    return "unknown";
}

// ============================================================================
// Mode Bits - Represented as uint32_t (octal 0755, 0644, etc.)
// ============================================================================

struct ModeBits {
    // Standard Unix mode bits
    bool owner_read = false;
    bool owner_write = false;
    bool owner_exec = false;
    bool group_read = false;
    bool group_write = false;
    bool group_exec = false;
    bool other_read = false;
    bool other_write = false;
    bool other_exec = false;
    
    // Special bits
    bool setuid = false;
    bool setgid = false;
    bool sticky_bit = false;
    
    uint32_t value() const {
        uint32_t result = 0;
        
        if (owner_read)   result |= 0400;
        if (owner_write)  result |= 0200;
        if (owner_exec)   result |= 0100;
        if (group_read)   result |= 0040;
        if (group_write)  result |= 0020;
        if (group_exec)   result |= 0010;
        if (other_read)   result |= 0004;
        if (other_write)  result |= 0002;
        if (other_exec)   result |= 0001;
        
        if (setuid)       result |= 04000;
        if (setgid)       result |= 02000;
        if (sticky_bit)   result |= 01000;
        
        return result;
    }
    
    static ModeBits from_value(uint32_t v) {
        ModeBits m;
        m.owner_read = !!(v & 0400);
        m.owner_write = !!(v & 0200);
        m.owner_exec = !!(v & 0100);
        m.group_read = !!(v & 0040);
        m.group_write = !!(v & 0020);
        m.group_exec = !!(v & 0010);
        m.other_read = !!(v & 0004);
        m.other_write = !!(v & 0002);
        m.other_exec = !!(v & 0001);
        m.setuid = !!(v & 04000);
        m.setgid = !!(v & 02000);
        m.sticky_bit = !!(v & 01000);
        return m;
    }
};

// ============================================================================
// Ownership Reference - Who should own this artifact?
// ============================================================================

struct OwnerRef {
    // A stable owner reference - either by username, uid, group name, or gid
    enum class Kind {
        kByName,      // String-based lookup via NSS (username/group)
        kById,        // Numeric UID/GID (more stable but less portable)
    } kind;
    
    std::optional<std::string> name;  // Valid when kind == kByName
    std::optional<uid_t> id;          // Valid when kind == kById
    
    static OwnerRef by_name(std::string n) {
        OwnerRef r;
        r.kind = Kind::kByName;
        r.name = std::move(n);
        return r;
    }
    
    static OwnerRef by_uid(uid_t u) {
        OwnerRef r;
        r.kind = Kind::kById;
        r.id = u;
        return r;
    }
    
    static OwnerRef by_gid(gid_t g) {
        OwnerRef r;
        r.kind = Kind::kById;
        r.id = static_cast<uid_t>(g);
        return r;
    }
};

// ============================================================================
// Evidence and Result Types
// ============================================================================

struct PermissionEvidence {
    std::string source;              // e.g., "stat", "lstat", "getpwnam"
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::string> captured_value;  // original value before mutation
};

template <typename T>
struct PermissionResult {
    enum class Status {
        kSuccess,
        kNotFound,           // User/group not found via NSS
        kInvalid,            // Invalid mode/owner reference
        kPermissionDenied,   // Insufficient privilege to perform operation
        kUnknown,            // Could not determine (acquisition failed)
        kVerificationFailed, // Postcondition verification failed
    } status = Status::kUnknown;
    
    std::optional<T> value;
    std::string error_code;
    std::string error_message;
    std::vector<PermissionEvidence> evidence;
    
    bool is_success() const { return status == Status::kSuccess && value.has_value(); }
    bool is_not_found() const { return status == Status::kNotFound; }
    bool is_invalid() const { return status == Status::kInvalid; }
    bool is_permission_denied() const { return status == Status::kPermissionDenied; }
    bool is_unknown() const { return status == Status::kUnknown; }
    bool is_verification_failed() const { return status == Status::kVerificationFailed; }
    
    static PermissionResult<T> success(T v, std::string source) {
        PermissionResult<T> r;
        r.status = Status::kSuccess;
        r.value = std::move(v);
        r.error_code = "";
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PermissionResult<T> not_found(std::string source, std::string msg) {
        PermissionResult<T> r;
        r.status = Status::kNotFound;
        r.error_code = kErrorNoSuchUser;
        r.error_message = std::move(msg);
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PermissionResult<T> invalid(std::string source, std::string msg) {
        PermissionResult<T> r;
        r.status = Status::kInvalid;
        r.error_code = kErrorInvalidMode;
        r.error_message = std::move(msg);
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PermissionResult<T> permission_denied(std::string source, std::string msg) {
        PermissionResult<T> r;
        r.status = Status::kPermissionDenied;
        r.error_code = kErrorPermissionDenied;
        r.error_message = std::move(msg);
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PermissionResult<T> unknown(std::string source, std::string msg) {
        PermissionResult<T> r;
        r.status = Status::kUnknown;
        r.error_code = kErrorAcquisitionFailed;
        r.error_message = std::move(msg);
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PermissionResult<T> verification_failed(std::string source, std::string msg) {
        PermissionResult<T> r;
        r.status = Status::kVerificationFailed;
        r.error_code = kErrorRepairFailed;
        r.error_message = std::move(msg);
        PermissionEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
};

// ============================================================================
// File State Observation
// ============================================================================

enum class SymlinkSafety {
    kAllowed,          // Symlinks are acceptable (for read-only operations)
    kRejected,         // Symlinks must be rejected (for write operations)
    kUnknown,          // Could not determine
};

struct FileState {
    std::filesystem::path path;
    
    bool exists = false;           // Path exists (or parent directory for files)
    bool is_regular_file = false;  // Is a regular file?
    bool is_directory = false;     // Is a directory?
    bool is_symlink = false;       // Is a symlink? (use lstat to detect)
    
    std::optional<uid_t> uid;
    std::optional<gid_t> gid;
    
    ModeBits mode_bits;
    
    std::chrono::system_clock::time_point mtime;
    off_t size = 0;
    
    // Symlink target (only set if is_symlink == true)
    std::optional<std::filesystem::path> symlink_target;
};

// ============================================================================
// Observation API - What is the current state?
// ============================================================================

PermissionResult<FileState> observe_file_state(const std::filesystem::path& path, 
                                                 SymlinkSafety symlink_safety = SymlinkSafety::kAllowed);

// Specialization for void - not needed in most cases

PermissionResult<uid_t> resolve_owner_uid(const OwnerRef& owner_ref);
PermissionResult<gid_t> resolve_group_gid(const OwnerRef& group_ref);

// ============================================================================
// Permission Verification - Is the current state correct?
// ============================================================================

struct PermissionVerification {
    // File system checks
    bool path_exists = false;
    bool is_correct_type = false;  // Correct file/directory type
    bool is_not_symlink = false;   // Not a symlink (where not allowed)
    
    // Ownership checks
    bool owner_matches = false;    // UID matches expected
    bool group_matches = false;    // GID matches expected
    
    // Permission bits checks
    std::vector<std::pair<PermissionType, bool>> permission_checks;
    
    // Summary
    bool is_compliant = false;
    
    std::string verification_source;
};

struct VerifyOwnershipIntent {
    std::filesystem::path path;
    
    std::optional<uid_t> expected_uid;
    std::optional<gid_t> expected_gid;
    
    ModeBits expected_mode_bits;
    
    SymlinkSafety symlink_safety = SymlinkSafety::kRejected;
};

PermissionVerification verify_ownership(const VerifyOwnershipIntent& intent);

// ============================================================================
// Permission Operations - Mutate state
// ============================================================================

struct OwnershipMutation {
    std::filesystem::path path;
    
    // Optional: only mutate if current value differs from expected
    std::optional<uid_t> if_current_uid_not;   // Skip if uid matches
    std::optional<gid_t> if_current_gid_not;   // Skip if gid matches
    
    // Target state
    std::optional<uid_t> set_uid;
    std::optional<gid_t> set_gid;
    
    std::optional<ModeBits> set_mode_bits;
};

struct PermissionMutation {
    enum class Type {
        kChmod,           // Change file mode bits
        kChown,           // Change owner (uid/gid)
        kSetOwner,        // Set both uid and gid
    } type;
    
    std::filesystem::path path;
    ModeBits mode_bits;
};

struct PermissionOperationResult {
    bool changed = false;            // Was the state actually modified?
    bool verified = false;           // Postconditions independently verified
    
    // For verification failures
    std::optional<PermissionVerification> postcondition_observed;
    
        // For void results, use a separate helper
    // Note: This is intentionally left undefined for void specialization
    // Use result_for_type<T>() where T is not void for actual return values
};

PermissionOperationResult apply_ownership_mutation(const OwnershipMutation& mutation);
PermissionOperationResult apply_permission_change(const PermissionMutation& mutation);

// ============================================================================
// Safe Creation - Create files/directories with correct permissions
// ============================================================================

struct CreationIntent {
    std::filesystem::path path;
    
    // Type of artifact
    enum class Type {
        kFile,
        kDirectory,
        kParentDirectories,  // Create all parent directories
    } type = Type::kFile;
    
    ModeBits mode_bits;
    
    uid_t owner_uid;
    gid_t owner_gid;
};

struct CreationResult {
    bool created = false;            // New artifact was created
    bool already_existed = false;    // Already existed, verified permissions
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
    
    // Verification
    FileState postcondition_state;
};

CreationResult create_with_permissions(const CreationIntent& intent);

// ============================================================================
// Repair - Restore Rebuntu-owned artifacts to correct state
// ============================================================================

enum class RepairAction {
    kNoOp,                    // Already compliant
    kUpdateMode,              // chmod required
    kUpdateOwner,             // chown required
    kRecreate,                // Must recreate (symlink detected, wrong type)
};

struct RepairIssue {
    std::filesystem::path path;
    
    enum class Type {
        kMissingArtifact,
        kWrongPermissions,
        kWrongOwner,
        kSymlinkDetected,
        kWrongType,           // File when directory expected, or vice versa
        kUserModified,        // User has modified (do not repair silently)
        kUnknownOwnership,    // Cannot determine ownership
    } type;
    
    std::string description;
};

struct RepairPlan {
    std::vector<RepairIssue> issues;
    std::optional<std::string> error_message;
    bool is_empty() const { return issues.empty() && !error_message.has_value(); }
};

struct RepairResult {
    std::vector<RepairAction> actions_taken;
    
    bool any_changed = false;
    bool fully_verified = true;  // All postconditions verified
    
    PermissionVerification final_state;
};

// Analyze what repairs are needed
RepairPlan analyze_ownership_repairs(const std::vector<std::filesystem::path>& paths,
                                      const VerifyOwnershipIntent& intent);

// Execute repair actions (idempotent)
RepairResult execute_ownership_repair(const RepairPlan& plan, 
                                       const VerifyOwnershipIntent& intent);

// ============================================================================
// Umask Support
// ============================================================================

struct UmaskState {
    uint32_t current_umask;  // Current process umask
    
    // How the umask affects mode creation:
    // effective_mode = desired_mode & ~umask
    uint32_t effective_file_mode(uint32_t desired) const { return desired & ~current_umask; }
    uint32_t effective_dir_mode(uint32_t desired) const { return desired & ~current_umask; }
};

PermissionResult<UmaskState> observe_umask();
ModeBits mode_after_umask(ModeBits desired, uint32_t current_umask);

// ============================================================================
// Utility Functions
// ============================================================================

// Convert ModeBits to string for logging (e.g., "0755")
std::string mode_to_string(uint32_t mode);
std::string mode_bits_to_string(const ModeBits& bits);

// Parse permission string like "0755" or "rwxr-xr-x"
PermissionResult<ModeBits> parse_mode_string(std::string_view s);

}  // namespace rebuntu::environment::ownership