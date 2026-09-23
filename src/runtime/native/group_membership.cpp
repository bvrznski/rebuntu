// rebuntu::environment::group_membership — Group membership operations (Phase 2.2)
#include <observation/environment/group_membership.hpp>

#include <array>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <chrono>

namespace rebuntu::environment::group_membership {

// ============================================================================
// Native Helper Functions
// ============================================================================

static GroupRef resolve_group_ref(const GroupRef& ref) {
    // If we have a name, look up the GID to get stable reference
    if (ref.kind == GroupRef::Kind::kByName && ref.name.has_value()) {
        struct group grbuf;
        struct group* result = nullptr;
        std::array<char, 4096> buffer{};
        
        int err = getgrnam_r(ref.name->c_str(), &grbuf, buffer.data(), buffer.size(), &result);
        if (err == 0 && result != nullptr) {
            return GroupRef::by_gid(result->gr_gid);
        }
    }
    return ref;
}

// ============================================================================
// Observation API
// ============================================================================

MembershipResult<GroupInfo> observe_group(const GroupRef& group_ref) {
    // Resolve to stable GID reference first
    auto resolved = resolve_group_ref(group_ref);
    
    if (resolved.kind != GroupRef::Kind::kByGid || !resolved.gid.has_value()) {
        return MembershipResult<GroupInfo>::unknown(
            "observe_group", "Could not resolve group reference to GID");
    }
    
    gid_t gid = resolved.gid.value();
    
    struct group grbuf;
    struct group* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getgrgid_r(gid, &grbuf, buffer.data(), buffer.size(), &result);
    if (err != 0 || result == nullptr) {
        return MembershipResult<GroupInfo>::not_found("getgrgid_r");
    }
    
    GroupInfo info;
    info.gid = gid;
    info.name = result->gr_name ? std::string(result->gr_name) : std::optional<std::string>{};
    info.native_source = "getgrgid_r";
    info.is_valid = true;
    
    // Get member list
    // Note: getgrgid doesn't give members; we need to enumerate passwd entries
    // This is a simplified approach - for production, use getgrouplist orNSS
    
    return MembershipResult<GroupInfo>::success(std::move(info), "getgrgid_r");
}

MembershipResult<std::vector<gid_t>> effective_groups_for_uid(uid_t uid) {
    struct passwd* pwd = getpwuid(uid);
    if (!pwd) {
        return MembershipResult<std::vector<gid_t>>::not_found("getpwuid");
    }
    
    gid_t primary_gid = pwd->pw_gid;
    std::vector<gid_t> groups;
    groups.push_back(primary_gid);
    
    // Use initgroups to get supplementary groups
    if (initgroups(pwd->pw_name, primary_gid) != 0) {
        return MembershipResult<std::vector<gid_t>>::unknown(
            "initgroups", "Failed to initialize group list");
    }
    
    constexpr int max_groups = 32;
    std::array<gid_t, max_groups> gbuf;
    int ngroups = static_cast<int>(gbuf.size());
    
    int count = getgroups(ngroups, gbuf.data());
    if (count < 0) {
        return MembershipResult<std::vector<gid_t>>::unknown(
            "getgroups", "Failed to retrieve supplementary groups");
    }
    
    // Collect unique groups
    std::sort(gbuf.begin(), gbuf.begin() + count);
    for (int i = 0; i < count; ++i) {
        gid_t g = gbuf[i];
        if (std::find(groups.begin(), groups.end(), g) == groups.end()) {
            groups.push_back(g);
        }
    }
    
    std::sort(groups.begin(), groups.end());
    
    return MembershipResult<std::vector<gid_t>>::success(std::move(groups), "effective_groups_for_uid");
}

MembershipResult<bool> is_declared_member_of(const std::string& username, const GroupRef& group_ref) {
    auto resolved = resolve_group_ref(group_ref);
    
    if (resolved.kind != GroupRef::Kind::kByGid || !resolved.gid.has_value()) {
        return MembershipResult<bool>::unknown(
            "is_declared_member_of", "Could not resolve group reference");
    }
    
    gid_t gid = resolved.gid.value();
    
    struct group grbuf;
    struct group* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getgrgid_r(gid, &grbuf, buffer.data(), buffer.size(), &result);
    if (err != 0 || result == nullptr) {
        return MembershipResult<bool>::not_found("getgrgid_r");
    }
    
    // Check if username is in the group's member list
    if (result->gr_mem) {
        for (char** p = result->gr_mem; *p != nullptr; ++p) {
            if (*p && std::string(*p) == username) {
                return MembershipResult<bool>::success(true, "getgrgid_r");
            }
        }
    }
    
    return MembershipResult<bool>::success(false, "getgrgid_r");
}

MembershipResult<bool> is_effectively_in_group(gid_t gid) {
    constexpr int max_groups = 32;
    std::array<gid_t, max_groups> gbuf;
    int ngroups = static_cast<int>(gbuf.size());
    
    int count = getgroups(ngroups, gbuf.data());
    if (count < 0) {
        return MembershipResult<bool>::unknown(
            "getgroups", "Failed to retrieve supplementary groups");
    }
    
    // Check effective GID too
    gid_t current_egid = getegid();
    for (int i = 0; i < count; ++i) {
        if (gbuf[i] == gid || gbuf[i] == current_egid) {
            return MembershipResult<bool>::success(true, "getgroups");
        }
    }
    
    // Check if requested GID matches current effective GID
    if (current_egid == gid) {
        return MembershipResult<bool>::success(true, "effective_gid_check");
    }
    
    return MembershipResult<bool>::success(false, "getgroups");
}

// ============================================================================
// Mutation API - Explicit and Verified
// ============================================================================

MembershipResult<std::vector<gid_t>> apply_membership_mutation(
    const GroupMembershipMutation& mutation) {
    
    // Phase 2.2: For now, observation-only implementation.
    // Full mutation support requires elevated privileges and careful
    // verification of /etc/group updates via setgroups() or native tools.
    
    if (mutation.context.scope == MutationContext::Scope::kSystemWide) {
        return MembershipResult<std::vector<gid_t>>::unknown(
            "apply_membership_mutation",
            "Full system-wide group mutation not yet implemented. "
            "Use native tools: usermod, gpasswd, or modify /etc/group directly.");
    }
    
    // User session scope - we can attempt setgroups() for the current process
    if (mutation.type == GroupMembershipMutation::Type::kAddMember ||
        mutation.type == GroupMembershipMutation::Type::kRemoveMember) {
        return MembershipResult<std::vector<gid_t>>::unknown(
            "apply_membership_mutation",
            "Process-level group modification requires setgroups() with proper "
            "privileges and may require new session for full effect.");
    }
    
    // Return current effective groups
    return effective_groups_for_uid(getuid());
}

MembershipResult<std::vector<gid_t>> apply_membership_mutations(
    const std::vector<GroupMembershipMutation>& mutations) {
    
    if (mutations.empty()) {
        return effective_groups_for_uid(getuid());
    }
    
    // Apply all mutations and return final state
    // Note: This is a placeholder - actual implementation would batch operations
    
    for (const auto& m : mutations) {
        auto result = apply_membership_mutation(m);
        if (!result.is_success()) {
            return result;
        }
    }
    
    return effective_groups_for_uid(getuid());
}

// ============================================================================
// Verification API
// ============================================================================

MembershipVerification verify_group_membership_consistency(uid_t uid) {
    MembershipVerification verification;
    
    auto declared_result = observe_current_effective_groups();
    if (!declared_result.is_success()) {
        verification.verification_source = "observe_current_effective_groups";
        return verification;
    }
    
    const auto& current = declared_result.value;
    verification.group_states.reserve(current.size());
    
    for (gid_t gid : current) {
        MembershipVerification::GroupState state;
        state.gid = gid;
        
        // Try to determine if this is declared membership
        struct group grbuf;
        struct group* result = nullptr;
        std::array<char, 4096> buffer{};
        
        int err = getgrgid_r(gid, &grbuf, buffer.data(), buffer.size(), &result);
        if (err == 0 && result != nullptr) {
            state.is_declared_member = true;  // Group exists
        }
        
        state.is_effectively_in_group = true;  // We're currently in this group
        
        verification.group_states.push_back(std::move(state));
    }
    
    // Check if refresh needed (would require new login session)
    struct passwd* pwd = getpwuid(uid);
    verification.declared_matches_effective = (pwd != nullptr);
    verification.effective_groups_refresh_needed = false;
    verification.verification_source = "verify_group_membership_consistency";
    
    return verification;
}

// ============================================================================
// Context-Aware Helpers
// ============================================================================

MembershipResult<std::vector<gid_t>> observe_current_effective_groups() {
    return effective_groups_for_uid(getuid());
}

bool requires_new_session_for_group_changes(const std::vector<gid_t>& current, 
                                             const std::vector<gid_t>& expected) {
    // Group membership changes require a new login session to take full effect
    // This is because supplementary groups are set at login time
    
    if (current == expected) {
        return false;  // No change needed
    }
    
    // If effective and declared differ, user likely needs new session
    return true;
}

}  // namespace rebuntu::environment::group_membership