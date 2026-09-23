// rebuntu::environment::user_identity — User identity context (Phase 2.1)
//
// This module provides typed user identity information using Linux/NSS as the
// authoritative source.
//
// Phase 2.1 adds:
//   * Typed errors for all identity operations
//   * Evidence-based observations with provenance
//   * Comprehensive supplementary group lookup
//   * Safe home directory resolution via NSS only (no string concatenation)
//   * Verification capabilities for identity state

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <cstdint>
#include <string_view>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::environment::user_identity {

// ============================================================================
// Identity Types
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
// Error Codes
// ============================================================================

inline constexpr std::string_view kErrorNoSuchUser = "E_NO_SUCH_USER";
inline constexpr std::string_view kErrorNoSuchGroup = "E_NO_SUCH_GROUP";
inline constexpr std::string_view kErrorAcquisitionFailed = "E_ACQUISITION_FAILED";
inline constexpr std::string_view kErrorPermissionDenied = "E_PERMISSION_DENIED";

// ============================================================================
// Evidence and Result Types
// ============================================================================

struct IdentityEvidence {
    std::string source;
    std::string observed_value;
    std::string captured_at;
};

template <typename T>
struct IdentityResult {
    enum class Status {
        kSuccess,
        kNotFound,
        kUnknown,
        kPermissionDenied,
    } status = Status::kUnknown;
    
    T value;
    std::string error_code;
    std::string error_message;
    std::vector<IdentityEvidence> evidence;
    
    bool is_success() const { return status == Status::kSuccess; }
    bool is_not_found() const { return status == Status::kNotFound; }
    bool is_unknown() const { return status == Status::kUnknown; }
    bool is_permission_denied() const { return status == Status::kPermissionDenied; }
    
    static IdentityResult<T> success(T v, std::string source) {
        IdentityResult<T> r;
        r.status = Status::kSuccess;
        r.value = std::move(v);
        r.error_code = "";
        IdentityEvidence e;
        e.source = std::move(source);
        e.captured_at = "2024-01-01T00:00:00Z";
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static IdentityResult<T> not_found(std::string source) {
        IdentityResult<T> r;
        r.status = Status::kNotFound;
        r.error_code = std::string(kErrorNoSuchUser);
        r.error_message = "User or group not found";
        IdentityEvidence e;
        e.source = std::move(source);
        e.observed_value = "";
        e.captured_at = "2024-01-01T00:00:00Z";
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static IdentityResult<T> unknown(std::string source, std::string msg) {
        IdentityResult<T> r;
        r.status = Status::kUnknown;
        r.error_code = std::string(kErrorAcquisitionFailed);
        r.error_message = std::move(msg);
        IdentityEvidence e;
        e.source = std::move(source);
        e.observed_value = "";
        e.captured_at = "2024-01-01T00:00:00Z";
        r.evidence.push_back(std::move(e));
        return r;
    }
};

// ============================================================================
// UserIdentity Structure
// ============================================================================

struct UserIdentity {
    std::optional<std::string> username;
    std::optional<uid_t> uid;
    std::optional<gid_t> gid;
    
    std::optional<uid_t> effective_uid;
    std::optional<gid_t> effective_gid;
    
    std::optional<uid_t> saved_uid;
    std::optional<gid_t> saved_gid;
    
    std::optional<std::string> home_dir;
    
    std::optional<std::string> xdg_config_home;
    std::optional<std::string> xdg_data_home;
    std::optional<std::string> xdg_cache_home;
    
    std::optional<gid_t> primary_gid;
    std::vector<gid_t> supplementary_groups;
    
    bool is_root = false;
    bool is_sudo = false;
    
    IdentityType identity_type = IdentityType::kEffective;
};

struct UserContext {
    UserIdentity identity;
    
    bool xdg_runtime_dir_exists = false;
    std::optional<std::string> xdg_runtime_dir;
    
    enum class Status {
        kComplete,
        kPartial,
        kUnknown,
    } status = Status::kUnknown;
};

// ============================================================================
// Native User Lookup Functions (Phase 2.1)
// ============================================================================

IdentityResult<std::string> username_for_uid(uid_t uid);
IdentityResult<std::string> home_dir_for_uid(uid_t uid);
IdentityResult<gid_t> primary_gid_for_uid(uid_t uid);
IdentityResult<std::vector<gid_t>> supplementary_groups_for_uid(uid_t uid);

IdentityResult<std::string> uid_for_username(const std::string& username);
IdentityResult<gid_t> gid_for_groupname(const std::string& groupname);
IdentityResult<std::vector<gid_t>> all_groups_for_uid(uid_t uid);

// ============================================================================
// Identity Verification
// ============================================================================

struct IdentityVerification {
    bool uid_consistent = false;
    bool gid_consistent = false;
    bool effective_matches_real = false;
    bool is_root_state_is_sane = false;
    std::vector<std::string> warnings;
};

IdentityVerification verify_identity_integrity();

// ============================================================================
// Identity Context Construction (Phase 2.1)
// ============================================================================

UserContext construct_user_context();
UserIdentity build_current_process_identity();

bool is_running_under_sudo();
uid_t get_real_uid_when_elevated();

// ============================================================================
// XDG Directory Helpers
// ============================================================================

std::string get_xdg_config_home(const UserContext& context);
std::string get_xdg_data_home(const UserContext& context);
std::string get_xdg_cache_home(const UserContext& context);

IdentityResult<std::string> get_xdg_runtime_dir();

// ============================================================================
// Safe Path Resolution
// ============================================================================

struct UserXdgDirectories {
    std::optional<std::string> config;
    std::optional<std::string> data;
    std::optional<std::string> cache;
};

IdentityResult<UserXdgDirectories> resolve_user_xdg_directories(uid_t uid);

}  // namespace rebuntu::environment::user_identity