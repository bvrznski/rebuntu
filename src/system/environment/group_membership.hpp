// rebuntu::environment::group_membership — Group membership primitives (Phase 2.2)
//
// This module provides typed interfaces for group membership operations.
// It distinguishes between:
//   * Linux groups (native authorization facts observed via /etc/group, NSS)
//   * Declared membership (what's in /etc/group or provider records)
//   * Effective membership (what groups a process/user currently has)
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/
//
// Phase 2.1 established identity observation.
// Phase 2.2 adds explicit membership operations and verification.

#pragma once

#include <system/environment/user_identity.hpp>
#include <string>
#include <vector>
#include <optional>
#include <chrono>
#include <cstdint>

namespace rebuntu::environment::group_membership {

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorNoSuchGroup[] = "E_NO_SUCH_GROUP";
inline constexpr char kErrorNoSuchUser[] = "E_NO_SUCH_USER";
inline constexpr char kErrorAlreadyMember[] = "E_ALREADY_MEMBER";
inline constexpr char kErrorNotMember[] = "E_NOT_MEMBER";
inline constexpr char kErrorAcquisitionFailed[] = "E_ACQUISITION_FAILED";
inline constexpr char kErrorPermissionDenied[] = "E_PERMISSION_DENIED";

// ============================================================================
// Group Reference Types
// ============================================================================

struct GroupRef {
    // A stable group reference - either by name or GID
    // Must revalidate before mutation (GIDs can be reused)
    
    enum class Kind {
        kByName,  // String-based lookup via NSS
        kByGid,   // Numeric GID lookup
    } kind;
    
    std::optional<std::string> name;  // Valid when kind == kByName
    std::optional<gid_t> gid;         // Valid when kind == kByGid
    
    static GroupRef by_name(std::string n) {
        GroupRef r;
        r.kind = Kind::kByName;
        r.name = std::move(n);
        return r;
    }
    
    static GroupRef by_gid(gid_t g) {
        GroupRef r;
        r.kind = Kind::kByGid;
        r.gid = g;
        return r;
    }
};

inline bool operator==(const GroupRef& a, const GroupRef& b) {
    if (a.kind != b.kind) return false;
    if (a.kind == GroupRef::Kind::kByName) {
        return a.name == b.name || (a.name && b.name && *a.name == *b.name);
    }
    return a.gid == b.gid;
}

inline bool operator!=(const GroupRef& a, const GroupRef& b) {
    return !(a == b);
}

// ============================================================================
// Evidence and Result Types
// ============================================================================

struct MembershipEvidence {
    std::string source;              // e.g., "getgrouplist", "setgroups"
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::string> captured_value;  // e.g., original value before mutation
};

template <typename T>
struct MembershipResult {
    enum class Status {
        kSuccess,
        kNotFound,
        kAlreadyExists,   // For mutations - item already in desired state
        kMissing,         // For mutations - item not in expected state
        kUnknown,
        kPermissionDenied,
    } status = Status::kUnknown;
    
    T value;
    std::string error_code;
    std::string error_message;
    std::vector<MembershipEvidence> evidence;
    
    bool is_success() const { return status == Status::kSuccess; }
    bool is_not_found() const { return status == Status::kNotFound; }
    bool is_already_exists() const { return status == Status::kAlreadyExists; }
    bool is_missing() const { return status == Status::kMissing; }
    bool is_unknown() const { return status == Status::kUnknown; }
    bool is_permission_denied() const { return status == Status::kPermissionDenied; }
    
    static MembershipResult<T> success(T v, std::string source) {
        MembershipResult<T> r;
        r.status = Status::kSuccess;
        r.value = std::move(v);
        r.error_code = "";
        MembershipEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static MembershipResult<T> not_found(std::string source) {
        MembershipResult<T> r;
        r.status = Status::kNotFound;
        r.error_code = kErrorNoSuchGroup;
        r.error_message = "Group or user not found";
        MembershipEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static MembershipResult<T> already_exists(std::string source, std::string msg) {
        MembershipResult<T> r;
        r.status = Status::kAlreadyExists;
        r.error_code = kErrorAlreadyMember;
        r.error_message = std::move(msg);
        MembershipEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static MembershipResult<T> missing(std::string source, std::string msg) {
        MembershipResult<T> r;
        r.status = Status::kMissing;
        r.error_code = kErrorNotMember;
        r.error_message = std::move(msg);
        MembershipEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static MembershipResult<T> unknown(std::string source, std::string msg) {
        MembershipResult<T> r;
        r.status = Status::kUnknown;
        r.error_code = kErrorAcquisitionFailed;
        r.error_message = std::move(msg);
        MembershipEvidence e;
        e.source = std::move(source);
        e.observed_at = std::chrono::system_clock::now();
        r.evidence.push_back(std::move(e));
        return r;
    }
};

// ============================================================================
// Group Information
// ============================================================================

struct GroupInfo {
    std::optional<std::string> name;       // Group name from NSS
    std::optional<gid_t> gid;              // Numeric group ID
    std::vector<uid_t> members;            // Member UIDs (effective membership)
    bool is_valid = false;                 // Whether this represents a real system group
    
    // Source tracking for evidence
    std::string native_source;
};

// ============================================================================
// Observation API
// ============================================================================

MembershipResult<GroupInfo> observe_group(const GroupRef& group_ref);
MembershipResult<std::vector<gid_t>> effective_groups_for_uid(uid_t uid);

// Check if user is declared member of group (in /etc/group)
MembershipResult<bool> is_declared_member_of(const std::string& username, const GroupRef& group_ref);

// Check if process currently has group in its supplementary groups
MembershipResult<bool> is_effectively_in_group(gid_t gid);

// ============================================================================
// Mutation API - Explicit and Verified
//
// All mutations follow the pattern:
//   1. Resolve exact target (user + group refs)
//   2. Observe current state
//   3. Validate mutation is valid and authorized
//   4. Apply native mutation
//   5. Re-observe to verify postcondition
//
// ============================================================================

struct MutationContext {
    // The user whose membership changes
    uid_t target_uid;
    
    // Optional scope - user session vs system-wide
    enum class Scope {
        kUserSession,  // Affects current process/session only
        kSystemWide,   // Modifies /etc/group or provider record
    } scope = Scope::kSystemWide;
    
    // Authorization context (to be defined in Phase 5.x)
    std::optional<std::string> authorization_id;
};

struct GroupMembershipMutation {
    enum class Type {
        kAddMember,      // Add user to group's member list
        kRemoveMember,   // Remove user from group's member list
        kSetMembers,     // Replace entire member list (idempotent)
    } type;
    
    GroupRef group_ref;  // Target group
    uid_t user_uid;      // User being added/removed
    
    MutationContext context;  // Scope and authorization context
};

// Apply a single mutation. Returns effective membership after mutation.
MembershipResult<std::vector<gid_t>> apply_membership_mutation(const GroupMembershipMutation& mutation);

// Batch mutations with atomic semantics where possible
MembershipResult<std::vector<gid_t>> apply_membership_mutations(
    const std::vector<GroupMembershipMutation>& mutations);

// ============================================================================
// Verification API
// ============================================================================

struct MembershipVerification {
    // Whether declared membership (in /etc/group) matches effective membership
    bool declared_matches_effective = false;
    
    // For each group, track both states
    struct GroupState {
        gid_t gid;
        std::optional<bool> is_declared_member;
        std::optional<bool> is_effectively_in_group;
    };
    std::vector<GroupState> group_states;
    
    // Session state awareness
    bool effective_groups_refresh_needed = false;  // User needs new session for changes
    
    std::string verification_source;
};

MembershipVerification verify_group_membership_consistency(uid_t uid);

// ============================================================================
// Context-Aware Helpers
// ============================================================================

// Get membership info for current process
MembershipResult<std::vector<gid_t>> observe_current_effective_groups();

// Check if a user needs to log in again for group changes to take effect
bool requires_new_session_for_group_changes(const std::vector<gid_t>& current, 
                                             const std::vector<gid_t>& expected);

}  // namespace rebuntu::environment::group_membership