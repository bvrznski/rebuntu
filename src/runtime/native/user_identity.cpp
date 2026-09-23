// rebuntu::environment::user_identity — User identity context (Phase 2.1)
#include <observation/environment/user_identity.hpp>

#include <array>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <optional>
#include <pwd.h>
#include <unistd.h>
#include <grp.h>
#include <ctime>
#include <algorithm>

namespace rebuntu::environment::user_identity {

// ============================================================================
// Native User Lookup Functions (Phase 2.1)
// ============================================================================

IdentityResult<std::string> username_for_uid(uid_t uid) {
    struct passwd pwbuf;
    struct passwd* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getpwuid_r(uid, &pwbuf, buffer.data(), buffer.size(), &result);
    if (err == 0 && result != nullptr && result->pw_name != nullptr) {
        return IdentityResult<std::string>::success(std::string(result->pw_name), "getpwuid_r");
    }
    
    if (err == ENOENT || err == ESRCH) {
        return IdentityResult<std::string>::not_found("getpwuid_r");
    }
    
    return IdentityResult<std::string>::unknown(
        "getpwuid_r", std::string("Failed to lookup username for UID: ") + std::strerror(err));
}

IdentityResult<std::string> home_dir_for_uid(uid_t uid) {
    struct passwd pwbuf;
    struct passwd* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getpwuid_r(uid, &pwbuf, buffer.data(), buffer.size(), &result);
    if (err == 0 && result != nullptr && result->pw_dir != nullptr) {
        return IdentityResult<std::string>::success(std::string(result->pw_dir), "getpwuid_r");
    }
    
    if (err == ENOENT || err == ESRCH) {
        return IdentityResult<std::string>::not_found("getpwuid_r");
    }
    
    return IdentityResult<std::string>::unknown(
        "getpwuid_r", std::string("Failed to lookup home directory for UID: ") + std::strerror(err));
}

IdentityResult<gid_t> primary_gid_for_uid(uid_t uid) {
    struct passwd pwbuf;
    struct passwd* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getpwuid_r(uid, &pwbuf, buffer.data(), buffer.size(), &result);
    if (err == 0 && result != nullptr) {
        return IdentityResult<gid_t>::success(result->pw_gid, "getpwuid_r");
    }
    
    if (err == ENOENT || err == ESRCH) {
        return IdentityResult<gid_t>::not_found("getpwuid_r");
    }
    
    return IdentityResult<gid_t>::unknown(
        "getpwuid_r", std::string("Failed to lookup primary GID for UID: ") + std::strerror(err));
}

IdentityResult<std::vector<gid_t>> supplementary_groups_for_uid(uid_t uid) {
    constexpr int max_groups = 32;
    std::vector<gid_t> groups(max_groups);
    struct passwd* pwd = getpwuid(uid);
    
    if (!pwd) {
        return IdentityResult<std::vector<gid_t>>::not_found("getpwuid");
    }
    
    gid_t primary_gid = pwd->pw_gid;
    int ngroups = max_groups;
    
    if (initgroups(pwd->pw_name, primary_gid) != 0) {
        return IdentityResult<std::vector<gid_t>>::unknown(
            "initgroups", "Failed to initialize group list");
    }
    
    int err = getgroups(ngroups, groups.data());
    
    if (err >= 0) {
        groups.resize(err);
        std::sort(groups.begin(), groups.end());
        return IdentityResult<std::vector<gid_t>>::success(groups, "getgrouplist");
    }
    
    return IdentityResult<std::vector<gid_t>>::unknown(
        "getgroups", "Failed to retrieve supplementary groups");
}

IdentityResult<std::string> uid_for_username(const std::string& username) {
    struct passwd pwbuf;
    struct passwd* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getpwnam_r(username.c_str(), &pwbuf, buffer.data(), buffer.size(), &result);
    if (err == 0 && result != nullptr) {
        return IdentityResult<std::string>::success(
            std::to_string(result->pw_uid), "getpwnam_r");
    }
    
    if (err == ENOENT || err == ESRCH) {
        return IdentityResult<std::string>::not_found("getpwnam_r");
    }
    
    return IdentityResult<std::string>::unknown(
        "getpwnam_r", std::string("Failed to lookup UID for username: ") + username);
}

IdentityResult<gid_t> gid_for_groupname(const std::string& groupname) {
    struct group grbuf;
    struct group* result = nullptr;
    std::array<char, 4096> buffer{};
    
    int err = getgrnam_r(groupname.c_str(), &grbuf, buffer.data(), buffer.size(), &result);
    if (err == 0 && result != nullptr) {
        return IdentityResult<gid_t>::success(result->gr_gid, "getgrnam_r");
    }
    
    if (err == ENOENT || err == ESRCH) {
        return IdentityResult<gid_t>::not_found("getgrnam_r");
    }
    
    return IdentityResult<gid_t>::unknown(
        "getgrnam_r", std::string("Failed to lookup GID for groupname: ") + groupname);
}

IdentityResult<std::vector<gid_t>> all_groups_for_uid(uid_t uid) {
    struct passwd* pwd = getpwuid(uid);
    if (!pwd) {
        return IdentityResult<std::vector<gid_t>>::not_found("getpwuid");
    }
    
    std::vector<gid_t> groups;
    groups.push_back(pwd->pw_gid);
    
    auto supl_result = supplementary_groups_for_uid(uid);
    if (supl_result.is_success()) {
        for (gid_t gid : supl_result.value) {
            if (std::find(groups.begin(), groups.end(), gid) == groups.end()) {
                groups.push_back(gid);
            }
        }
    }
    
    std::sort(groups.begin(), groups.end());
    return IdentityResult<std::vector<gid_t>>::success(groups, "all_groups_for_uid");
}

// ============================================================================
// Identity Verification
// ============================================================================

IdentityVerification verify_identity_integrity() {
    IdentityVerification verification;
    
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    uid_t saved_uid = real_uid;
    
    gid_t real_gid = getgid();
    gid_t effective_gid = getegid();
    gid_t saved_gid = real_gid;
    
    verification.uid_consistent = (real_uid == saved_uid);
    verification.gid_consistent = (real_gid == saved_gid);
    verification.effective_matches_real = (effective_uid == real_uid && effective_gid == real_gid);
    verification.is_root_state_is_sane = (effective_uid == 0 || effective_uid != real_uid);
    
    if (!verification.uid_consistent) {
        verification.warnings.push_back("Real and saved UIDs differ unexpectedly");
    }
    
    return verification;
}

// ============================================================================
// Identity Context Construction
// ============================================================================

UserContext construct_user_context() {
    UserContext context;
    
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    UserIdentity& ident = context.identity;
    
    auto username_result = username_for_uid(effective_uid);
    if (username_result.is_success()) {
        ident.username = username_result.value;
    }
    
    ident.effective_uid = effective_uid;
    ident.effective_gid = getegid();
    ident.uid = real_uid;
    ident.gid = getgid();
    ident.saved_uid = real_uid;
    ident.saved_gid = getgid();
    
    auto home_result = home_dir_for_uid(effective_uid);
    if (!home_result.is_success()) {
        home_result = home_dir_for_uid(real_uid);
    }
    if (home_result.is_success()) {
        ident.home_dir = home_result.value;
    }
    
    auto primary_gid_result = primary_gid_for_uid(effective_uid);
    if (!primary_gid_result.is_success()) {
        primary_gid_result = primary_gid_for_uid(real_uid);
    }
    if (primary_gid_result.is_success()) {
        ident.primary_gid = primary_gid_result.value;
    }
    
    auto supl_groups_result = supplementary_groups_for_uid(effective_uid);
    if (!supl_groups_result.is_success()) {
        supl_groups_result = supplementary_groups_for_uid(real_uid);
    }
    if (supl_groups_result.is_success()) {
        ident.supplementary_groups = std::move(supl_groups_result.value);
    }
    
    ident.is_root = (effective_uid == 0);
    ident.is_sudo = is_running_under_sudo();
    ident.identity_type = IdentityType::kEffective;
    
    if (ident.home_dir.has_value()) {
        ident.xdg_config_home = get_xdg_config_home(context);
        ident.xdg_data_home = get_xdg_data_home(context);
        ident.xdg_cache_home = get_xdg_cache_home(context);
    }
    
    auto runtime_result = get_xdg_runtime_dir();
    if (runtime_result.is_success()) {
        context.xdg_runtime_dir = runtime_result.value;
    }
    if (context.xdg_runtime_dir.has_value() && std::filesystem::exists(context.xdg_runtime_dir.value())) {
        context.xdg_runtime_dir_exists = true;
    }
    
    bool has_uid = ident.uid.has_value() || ident.effective_uid.has_value();
    bool has_home = ident.home_dir.has_value();
    bool has_username = ident.username.has_value();
    
    if (has_uid && has_home && has_username) {
        context.status = UserContext::Status::kComplete;
    } else if (has_uid) {
        context.status = UserContext::Status::kPartial;
    } else {
        context.status = UserContext::Status::kUnknown;
    }
    
    return context;
}

UserIdentity build_current_process_identity() {
    UserIdentity ident;
    
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    auto username_result = username_for_uid(effective_uid);
    if (username_result.is_success()) {
        ident.username = username_result.value;
    }
    
    ident.uid = real_uid;
    ident.effective_uid = effective_uid;
    ident.saved_uid = real_uid;
    
    ident.gid = getgid();
    ident.effective_gid = getegid();
    ident.saved_gid = ident.gid;
    
    auto home_result = home_dir_for_uid(effective_uid);
    if (!home_result.is_success()) {
        home_result = home_dir_for_uid(real_uid);
    }
    if (home_result.is_success()) {
        ident.home_dir = home_result.value;
    }
    
    auto primary_gid_result = primary_gid_for_uid(effective_uid);
    if (!primary_gid_result.is_success()) {
        primary_gid_result = primary_gid_for_uid(real_uid);
    }
    if (primary_gid_result.is_success()) {
        ident.primary_gid = primary_gid_result.value;
    }
    
    auto supl_groups_result = supplementary_groups_for_uid(effective_uid);
    if (!supl_groups_result.is_success()) {
        supl_groups_result = supplementary_groups_for_uid(real_uid);
    }
    if (supl_groups_result.is_success()) {
        ident.supplementary_groups = std::move(supl_groups_result.value);
    }
    
    ident.is_root = (effective_uid == 0);
    ident.is_sudo = is_running_under_sudo();
    ident.identity_type = IdentityType::kEffective;
    
    return ident;
}

bool is_running_under_sudo() {
    const char* sudo_user = std::getenv("SUDO_USER");
    if (sudo_user == nullptr) {
        return false;
    }
    
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    if (effective_uid == 0 && real_uid != 0) {
        return true;
    }
    
    return false;
}

uid_t get_real_uid_when_elevated() {
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    if (effective_uid == 0 && real_uid != 0) {
        return real_uid;
    }
    
    return effective_uid;
}

// ============================================================================
// XDG Directory Helpers
// ============================================================================

std::string get_xdg_config_home(const UserContext& context) {
    const char* xdg_config = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config != nullptr && std::strlen(xdg_config) > 0) {
        return std::string(xdg_config);
    }
    
    if (context.identity.home_dir.has_value()) {
        return context.identity.home_dir.value() + "/.config";
    }
    return "/etc";
}

std::string get_xdg_data_home(const UserContext& context) {
    const char* xdg_data = std::getenv("XDG_DATA_HOME");
    if (xdg_data != nullptr && std::strlen(xdg_data) > 0) {
        return std::string(xdg_data);
    }
    
    if (context.identity.home_dir.has_value()) {
        return context.identity.home_dir.value() + "/.local/share";
    }
    return "/usr/local/share";
}

std::string get_xdg_cache_home(const UserContext& context) {
    const char* xdg_cache = std::getenv("XDG_CACHE_HOME");
    if (xdg_cache != nullptr && std::strlen(xdg_cache) > 0) {
        return std::string(xdg_cache);
    }
    
    if (context.identity.home_dir.has_value()) {
        return context.identity.home_dir.value() + "/.cache";
    }
    return "/var/cache";
}

IdentityResult<std::string> get_xdg_runtime_dir() {
    const char* xdg_runtime = std::getenv("XDG_RUNTIME_DIR");
    if (xdg_runtime != nullptr && std::strlen(xdg_runtime) > 0) {
        namespace fs = std::filesystem;
        if (fs::exists(xdg_runtime) && fs::is_directory(xdg_runtime)) {
            return IdentityResult<std::string>::success(std::string(xdg_runtime), "XDG_RUNTIME_DIR");
        }
    }
    
    return IdentityResult<std::string>::not_found("XDG_RUNTIME_DIR");
}

// ============================================================================
// Safe Path Resolution (Phase 2.1)
// ============================================================================

IdentityResult<UserXdgDirectories> resolve_user_xdg_directories(uid_t uid) {
    UserXdgDirectories dirs;
    
    auto home_result = home_dir_for_uid(uid);
    if (!home_result.is_success()) {
        return IdentityResult<UserXdgDirectories>::unknown(
            "resolve_user_xdg_directories", 
            "Could not resolve user home directory");
    }
    
    const std::string& home_dir = home_result.value;
    
    dirs.config = home_dir + "/.config";
    dirs.data = home_dir + "/.local/share";
    dirs.cache = home_dir + "/.cache";
    
    return IdentityResult<UserXdgDirectories>::success(dirs, "resolve_user_xdg_directories");
}

}  // namespace rebuntu::environment::user_identity