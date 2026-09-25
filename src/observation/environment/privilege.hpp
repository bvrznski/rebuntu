// rebuntu::environment::privilege — Privilege & Elevation Contract (Phase 2.4)
//
// This establishes Rebuntu's canonical privilege and elevation model:
//
//   PRIVILEGE = Execution authority (UID/GID, capabilities)
//   ELEVATION = Mechanism to gain privileged execution
//   SCOPE     = System vs User session context
//   IDENTITY  = Real vs Effective vs Saved UID/GID
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/
//
// Phase 2.1 established identity observation (uid_t, gid_t).
// Phase 2.4 adds privilege state and elevation capability detection.

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <cstdint>
#include <string_view>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

// Forward declare DiscoveryStatus (defined in discovery.hpp after includes)
namespace rebuntu::environment::discovery {
    enum class DiscoveryStatus;
}

#include <system/core/contracts.hpp>
#include <observation/environment/discovery.hpp>

// Undefine the forward declaration since we're including discovery.hpp which defines it
#undef DiscoveryStatus

namespace rebuntu::environment::privilege {

// ============================================================================
// Identity Types - UID/GID Context
// ============================================================================

enum class IdentityType {
    kReal,        // Real UID/GID (who the process truly is)
    kEffective,   // Effective UID/GID (what permissions are currently used)
    kSaved,       // Saved UID/GID (saved set-user-ID for privilege changes)
};

inline std::string_view to_string(IdentityType t) {
    switch (t) {
        case IdentityType::kReal:   return "real";
        case IdentityType::kEffective: return "effective";
        case IdentityType::kSaved:  return "saved";
    }
    return "unknown";
}

// ============================================================================
// Elevation Capability - Native Mechanism Detection
// ============================================================================

enum class ElevationCapability {
    kNone,           // No elevation mechanism available
    kSudoAvailable,  // sudo binary exists but may not be usable
    kSudoUsable,     // sudo works with current credentials
    kAlreadyElevated,// Process is already running as root (UID 0)
};

inline std::string_view to_string(ElevationCapability e) {
    switch (e) {
        case ElevationCapability::kNone:         return "none";
        case ElevationCapability::kSudoAvailable:return "sudo-available";
        case ElevationCapability::kSudoUsable:   return "sudo-usable";
        case ElevationCapability::kAlreadyElevated: return "already-elevated";
    }
    return "unknown";
}

// ============================================================================
// PrivilegeInfo - Current Privilege State
// ============================================================================

struct PrivilegeInfo {
    uid_t effective_uid = 0;           // geteuid()
    
    bool is_root = false;              // true if euid == 0
    
    ElevationCapability elevation = ElevationCapability::kNone;
    
    // Audit trail - who was the original user?
    std::optional<uid_t> real_uid;
    std::optional<std::string> sudo_user;  // SUDO_USER env var
    
    int status = 0;  // DiscoveryStatus placeholder (int until discovery.hpp is included)
};

// ============================================================================
// Scope Context - System vs User
// ============================================================================

enum class InstallationScope {
    kSystem,  // System-wide (euid == 0 or explicit --scope=system)
    kUser,    // Per-user (euid != 0 or explicit --scope=user)
};

inline std::string_view to_string(InstallationScope s) {
    switch (s) {
        case InstallationScope::kSystem: return "system";
        case InstallationScope::kUser:   return "user";
    }
    return "unknown";
}

struct ScopeContext {
    InstallationScope scope = InstallationScope::kUser;
    
    // For user scope
    std::optional<std::string> home_dir;
    
    // Audit trail for elevated processes
    std::optional<uid_t> original_uid;  // UID before elevation
    
    bool is_root = false;
};

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorNoPrivilege[] = "E_NO_PRIVILEGE";
inline constexpr char kErrorScopeMismatch[] = "E_SCOPE_MISMATCH";
inline constexpr char kErrorUnknownIdentity[] = "E_UNKNOWN_IDENTITY";

// ============================================================================
// Evidence and Result Types
// ============================================================================

struct PrivilegeEvidence {
    std::string source;              // e.g., "geteuid", "sudo_test"
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::string> captured_value;
};

template <typename T>
struct PrivilegeResult {
    enum class Status {
        kSuccess,
        kNotFound,           // User/group not found via NSS
        kInvalid,            // Invalid context
        kPermissionDenied,   // Insufficient privilege
        kUnknown,            // Could not determine (acquisition failed)
    } status = Status::kUnknown;
    
    std::optional<T> value;
    std::string error_code;
    std::string error_message;
    std::vector<PrivilegeEvidence> evidence;
    
    bool is_success() const { return status == Status::kSuccess && value.has_value(); }
    bool is_not_found() const { return status == Status::kNotFound; }
    bool is_invalid() const { return status == Status::kInvalid; }
    bool is_permission_denied() const { return status == Status::kPermissionDenied; }
    bool is_unknown() const { return status == Status::kUnknown; }
    
    static PrivilegeResult<T> success(T v, std::string source) {
        PrivilegeResult<T> r;
        r.status = Status::kSuccess;
        r.value = std::move(v);
        r.error_code = "";
        PrivilegeEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PrivilegeResult<T> not_found(std::string source, std::string msg) {
        PrivilegeResult<T> r;
        r.status = Status::kNotFound;
        r.error_code = kErrorUnknownIdentity;
        r.error_message = std::move(msg);
        PrivilegeEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PrivilegeResult<T> invalid(std::string source, std::string msg) {
        PrivilegeResult<T> r;
        r.status = Status::kInvalid;
        r.error_code = kErrorScopeMismatch;
        r.error_message = std::move(msg);
        PrivilegeEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PrivilegeResult<T> permission_denied(std::string source, std::string msg) {
        PrivilegeResult<T> r;
        r.status = Status::kPermissionDenied;
        r.error_code = kErrorNoPrivilege;
        r.error_message = std::move(msg);
        PrivilegeEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static PrivilegeResult<T> unknown(std::string source, std::string msg) {
        PrivilegeResult<T> r;
        r.status = Status::kUnknown;
        r.error_code = kErrorUnknownIdentity;
        r.error_message = std::move(msg);
        PrivilegeEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
};

// ============================================================================
// Identity Context - Full Process Identity
// ============================================================================

struct ProcessIdentity {
    uid_t real_uid = 0;
    uid_t effective_uid = 0;
    uid_t saved_uid = 0;
    
    gid_t real_gid = 0;
    gid_t effective_gid = 0;
    gid_t saved_gid = 0;
    
    bool is_root = false;
    ElevationCapability elevation = ElevationCapability::kNone;
    
    // Audit trail
    std::optional<std::string> sudo_user;  // SUDO_USER env var
    
    IdentityType identity_type = IdentityType::kEffective;
};

// ============================================================================
// Observation API - What is the current privilege state?
// ============================================================================

PrivilegeInfo discover_privilege();
ScopeContext discover_scope(const PrivilegeInfo& info);

// ============================================================================
// Verification API - Is this privilege state correct?
// ============================================================================

struct PrivilegeVerification {
    bool uid_consistent = false;        // real == saved
    bool euid_matches_context = false;  // effective matches scope requirements
    bool is_root_sane = false;          // root state is consistent
    
    std::optional<uid_t> observed_real_uid;
    std::optional<uid_t> observed_effective_uid;
    
    ElevationCapability expected_elevation = ElevationCapability::kNone;
    bool elevation_valid = false;
};

struct PrivilegeIntent {
    InstallationScope required_scope;
    
    std::optional<std::string> expected_home_dir;  // For user scope
    std::optional<uid_t> expected_original_uid;   // For sudo context
    
    // Verification mode
    bool strict = false;  // Fail if any inconsistency detected
};

PrivilegeVerification verify_privilege_state(
    const PrivilegeIntent& intent,
    const PrivilegeInfo& info);

// ============================================================================
// Identity Helper API
// ============================================================================

ProcessIdentity build_current_process_identity();

uid_t get_real_uid_when_elevated();

bool is_running_under_sudo();

std::optional<std::string> get_sudo_user_from_env();

}  // namespace rebuntu::environment::privilege