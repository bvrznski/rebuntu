// rebuntu::environment::scope — System/User/Session Scope Implementation (Phase 2.7)
// Phase 2.14 extension: systemd manager awareness
#include <observation/environment/scope.hpp>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <cerrno>

namespace rebuntu::environment::scope {

// ============================================================================
// XDGBases implementation - XDG Base Directory helpers
// ============================================================================

std::filesystem::path XDGBases::get_user_home() {
    const char* home_env = std::getenv("HOME");
    if (home_env && *home_env) {
        return std::filesystem::path(home_env);
    }
    
    // Fallback to passwd database
    uid_t uid = getuid();
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        return std::filesystem::path(result->pw_dir);
    }
    
    // Last resort - return empty path
    return std::filesystem::path();
}

// ============================================================================
// get_user_home() - Get user home directory (deprecated alias)
// ============================================================================

std::filesystem::path get_user_home() {
    const char* home_env = std::getenv("HOME");
    if (home_env && *home_env) {
        return std::filesystem::path(home_env);
    }
    
    // Fallback to passwd database
    uid_t uid = getuid();
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        return std::filesystem::path(result->pw_dir);
    }
    
    // Last resort - return empty path
    return std::filesystem::path();
}

// ============================================================================
// Systemd Manager State Discovery (Phase 2.14)
// ============================================================================

SystemdManagerState discover_systemd_manager_state() {
    SystemdManagerState state;
    
    uid_t euid = geteuid();
    bool is_root = (euid == 0);
    
    // Determine scope from effective UID
    if (is_root) {
        state.scope = ExecutionScope::kSystem;
        state.is_system_manager = true;
        state.system_unit_path = "/etc/systemd/system";
        
        // Check if systemctl command exists and is functional
        std::ifstream systemctl("/usr/bin/systemctl");
        if (systemctl.good()) {
            state.status = SystemdManagerStatus::kAvailable;
        } else {
            state.status = SystemdManagerStatus::kUnavailable;
        }
        
    } else {
        // Non-root - could be user or session scope
        state.scope = ExecutionScope::kUser;
        state.is_user_manager = true;
        
        const char* home_env = std::getenv("HOME");
        if (home_env && *home_env) {
            auto home = std::filesystem::path(home_env);
            state.user_unit_path = home / ".config" / "systemd" / "user";
            
            // Check XDG_RUNTIME_DIR for user manager availability
            const char* runtime_dir = std::getenv("XDG_RUNTIME_DIR");
            if (runtime_dir && *runtime_dir) {
                auto rt_path = std::filesystem::path(runtime_dir);
                
                // User systemd manager is available if runtime dir exists and we can 
                // access systemd user socket or have permission to query
                struct stat st;
                if (stat(rt_path.string().c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                    state.status = SystemdManagerStatus::kAvailable;
                    state.runtime_dir = rt_path;
                } else {
                    state.status = SystemdManagerStatus::kUnavailable;
                }
            } else {
                // No XDG_RUNTIME_DIR - user manager may not be available
                state.status = SystemdManagerStatus::kUnknown;
            }
        } else {
            state.status = SystemdManagerStatus::kUnknown;
        }
    }
    
    return state;
}

bool is_user_systemd_manager_available(uid_t uid) {
    if (uid == 0) {
        // Root doesn't have a user manager
        return false;
    }
    
    // Check XDG_RUNTIME_DIR for the specified UID
    const char* runtime_dir = std::getenv("XDG_RUNTIME_DIR");
    if (!runtime_dir || !*runtime_dir) {
        return false;
    }
    
    auto rt_path = std::filesystem::path(runtime_dir);
    struct stat st;
    
    if (stat(rt_path.string().c_str(), &st) != 0) {
        return false;
    }
    
    // Verify ownership matches UID
    uid_t current_uid = geteuid();
    if (st.st_uid != current_uid && current_uid != 0) {
        return false;
    }
    
    return true;
}

// ============================================================================
// Manager Path Resolver (Phase 2.14)
// ============================================================================

UnitPathInfo resolve_system_unit_path() {
    UnitPathInfo info;
    
    // System manager unit paths (always writable by root)
    std::vector<std::filesystem::path> candidates = {
        "/etc/systemd/system",
        "/usr/lib/systemd/system",
        "/run/systemd/system"
    };
    
    for (const auto& path : candidates) {
        std::error_code ec;
        if (std::filesystem::exists(path, ec)) {
            info.path = path;
            
            // Check write permission
            uid_t euid = geteuid();
            struct stat st;
            if (stat(path.string().c_str(), &st) == 0) {
                if (euid == 0 || (st.st_mode & S_IWUSR)) {
                    info.is_writable = true;
                } else {
                    info.error_message = "write permission denied";
                }
            }
            break;
        }
    }
    
    return info;
}

UnitPathInfo resolve_user_unit_path(const std::filesystem::path& home) {
    UnitPathInfo info;
    
    // User manager unit path
    auto user_systemd_dir = home / ".config" / "systemd";
    auto user_unit_path = user_systemd_dir / "user";
    
    std::error_code ec;
    
    if (std::filesystem::exists(user_systemd_dir, ec)) {
        info.path = user_unit_path;
        
        // Check write permission
        uid_t euid = geteuid();
        struct stat st;
        if (stat(home.string().c_str(), &st) == 0 && st.st_uid == euid) {
            info.is_writable = true;
        } else {
            info.error_message = "write permission denied";
        }
    } else {
        // Directory doesn't exist yet - can be created
        info.path = user_unit_path;
        info.is_writable = true;  // Can create if we have write to ~/.config
    }
    
    return info;
}

std::vector<std::filesystem::path> get_all_unit_paths(ExecutionScope scope) {
    std::vector<std::filesystem::path> paths;
    
    switch (scope) {
        case ExecutionScope::kSystem:
            // System manager unit search path order
            paths = {
                "/run/systemd/system",      // Runtime units
                "/etc/systemd/system",      // Admin units
                "/usr/lib/systemd/system"   // Package units
            };
            break;
            
        case ExecutionScope::kUser: {
            const char* home_env = std::getenv("HOME");
            if (home_env && *home_env) {
                auto home = std::filesystem::path(home_env);
                
                paths = {
                    home / ".config" / "systemd" / "user",
                    home / ".local" / "share" / "systemd" / "user"
                };
            }
            break;
        }
        
        case ExecutionScope::kSession:
            // Session scope doesn't have persistent unit files
            paths = {};
            break;
    }
    
    return paths;
}

// ============================================================================
// Scope Resolution: discover_context() - What is the current scope?
// ============================================================================

ScopeContext discover_context() {
    ScopeContext ctx;
    
    // Get identity
    ctx.effective_uid = geteuid();
    ctx.is_root = (ctx.effective_uid == 0);
    
    // Discover XDG base directories
    const char* xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_home && *xdg_config_home) {
        ctx.xdg.config_home = std::filesystem::path(xdg_config_home);
    } else {
        ctx.xdg.config_home = default_config_home();
    }
    
    const char* xdg_state_home = std::getenv("XDG_STATE_HOME");
    if (xdg_state_home && *xdg_state_home) {
        ctx.xdg.state_home = std::filesystem::path(xdg_state_home);
    } else {
        ctx.xdg.state_home = default_state_home();
    }
    
    const char* xdg_cache_home = std::getenv("XDG_CACHE_HOME");
    if (xdg_cache_home && *xdg_cache_home) {
        ctx.xdg.cache_home = std::filesystem::path(xdg_cache_home);
    } else {
        ctx.xdg.cache_home = default_cache_home();
    }
    
    const char* xdg_data_home = std::getenv("XDG_DATA_HOME");
    if (xdg_data_home && *xdg_data_home) {
        ctx.xdg.data_home = std::filesystem::path(xdg_data_home);
    } else {
        ctx.xdg.data_home = default_data_home();
    }
    
    // $XDG_RUNTIME_DIR only for non-root
    if (!ctx.is_root) {
        const char* xdg_runtime_dir = std::getenv("XDG_RUNTIME_DIR");
        if (xdg_runtime_dir && *xdg_runtime_dir) {
            ctx.xdg.runtime_dir = std::filesystem::path(xdg_runtime_dir);
        }
    }
    
    // Discover systemd manager state
    ctx.systemd_manager = discover_systemd_manager_state();
    
    // Determine scope from effective UID and systemd availability
    if (ctx.is_root && ctx.systemd_manager.status == SystemdManagerStatus::kAvailable) {
        ctx.scope = ExecutionScope::kSystem;
        
        // Capture original UID for sudo audit trail
        uid_t ruid = getuid();
        if (ruid != 0) {
            ctx.original_uid = ruid;
            
            const char* sudo_user = std::getenv("SUDO_USER");
            if (sudo_user) {
                ctx.sudo_user = std::string(sudo_user);
            }
        }
        
        // Set system paths
        ctx.bin_path = get_system_bin_path();
        ctx.config_dir = get_system_config_dir();
        ctx.state_dir = get_system_state_dir();
        ctx.cache_dir = get_system_cache_dir();
        
    } else {
        // Non-root - could be user or session scope
        ctx.scope = ExecutionScope::kUser;
        
        const char* home_env = std::getenv("HOME");
        if (home_env) {
            auto home = std::filesystem::path(home_env);
            
            ctx.bin_path = get_user_bin_path(home);
            ctx.config_dir = get_user_config_dir(home);
            ctx.state_dir = get_user_state_dir(home);
            ctx.cache_dir = get_user_cache_dir(home);
        }
        
        // XDG_RUNTIME_DIR indicates session context available
        if (ctx.xdg.runtime_dir.has_value()) {
            // Session scope available but default is still user for file storage
        }
    }
    
    return ctx;
}

// ============================================================================
// discover_context_for_uid() - Build scope context for a specific UID
// ============================================================================

ScopeContext discover_context_for_uid(uid_t uid) {
    ScopeContext ctx;
    
    ctx.effective_uid = uid;
    ctx.is_root = (uid == 0);
    
    // Get home directory for the target user
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        auto home = std::filesystem::path(result->pw_dir);
        
        // Determine scope based on UID
        if (ctx.is_root) {
            ctx.scope = ExecutionScope::kSystem;
            
            ctx.bin_path = get_system_bin_path();
            ctx.config_dir = get_system_config_dir();
            ctx.state_dir = get_system_state_dir();
            ctx.cache_dir = get_system_cache_dir();
            
        } else {
            ctx.scope = ExecutionScope::kUser;
            
            ctx.bin_path = get_user_bin_path(home);
            ctx.config_dir = get_user_config_dir(home);
            ctx.state_dir = get_user_state_dir(home);
            ctx.cache_dir = get_user_cache_dir(home);
        }
        
    } else {
        // Could not find user - use defaults
        ctx.scope = uid == 0 ? ExecutionScope::kSystem : ExecutionScope::kUser;
    }
    
    return ctx;
}

// ============================================================================
// resolve_explicit_scope() - Handle --scope= flag
// ============================================================================

std::optional<ExecutionScope> resolve_explicit_scope(
    const std::string& requested,
    const ScopeContext& current) {
    
    if (requested == "system" || requested == "sys") {
        // User wants system scope
        if (!current.is_root) {
            // Non-root requesting system scope - requires elevation
            return std::nullopt;  // Will be handled by caller with kRequireElevation
        }
        return ExecutionScope::kSystem;
    }
    
    if (requested == "user" || requested == "usr") {
        return ExecutionScope::kUser;
    }
    
    if (requested == "session" || requested == "sess") {
        // Session scope only valid for non-root with XDG_RUNTIME_DIR
        if (current.is_root) {
            return std::nullopt;  // Invalid for root
        }
        if (!current.xdg.runtime_dir.has_value()) {
            return std::nullopt;  // No session runtime directory available
        }
        return ExecutionScope::kSession;
    }
    
    // Unknown scope request
    return std::nullopt;
}

// ============================================================================
// default_scope_for_privilege() - Determine scope from privilege state
// ============================================================================

ExecutionScope default_scope_for_privilege(bool is_root) {
    return is_root ? ExecutionScope::kSystem : ExecutionScope::kUser;
}

// ============================================================================
// Scope Path API - Where do things go?
// ============================================================================

std::filesystem::path get_system_bin_path() {
    return "/usr/bin";
}

std::filesystem::path get_system_config_dir() {
    return "/etc/rebuntu";
}

std::filesystem::path get_system_state_dir() {
    return "/var/lib/rebuntu";
}

std::filesystem::path get_system_cache_dir() {
    return "/var/cache/rebuntu";
}

std::filesystem::path get_user_bin_path(const std::filesystem::path& home) {
    return home / ".local" / "bin";
}

std::filesystem::path get_user_config_dir(const std::filesystem::path& home) {
    return home / ".config" / "rebuntu";
}

std::filesystem::path get_user_state_dir(const std::filesystem::path& home) {
    return home / ".local" / "state" / "rebuntu";
}

std::filesystem::path get_user_cache_dir(const std::filesystem::path& home) {
    return home / ".cache" / "rebuntu";
}

std::filesystem::path get_session_runtime_dir(const ScopeContext& ctx) {
    if (ctx.xdg.runtime_dir.has_value()) {
        return *ctx.xdg.runtime_dir;
    }
    
    // Fallback
    if (ctx.effective_uid != 0 && ctx.effective_uid != std::numeric_limits<uid_t>::max()) {
        struct passwd pw;
        struct passwd* result = nullptr;
        char buf[4096];
        
        if (getpwuid_r(ctx.effective_uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
            auto home = std::filesystem::path(result->pw_dir);
            return home / ".cache" / "runtime";
        }
    }
    
    // Last resort
    return "/tmp/rebuntu-session-" + std::to_string(ctx.effective_uid);
}

// ============================================================================
// Cross-scope mediation - How do we handle requests for different scopes?
// ============================================================================

CrossScopeResult mediate_cross_scope_request(
    const ScopeContext& current,
    ExecutionScope requested) {
    
    // Same scope - always allowed
    if (current.scope == requested) {
        return CrossScopeResult::allow("requested scope matches current scope");
    }
    
    switch (requested) {
        case ExecutionScope::kSystem:
            // User requesting system scope - requires elevation
            if (!current.is_root) {
                return CrossScopeResult::require_elevation(
                    "system scope requires root privileges; "
                    "user requested but not running as root");
            }
            return CrossScopeResult::allow("root user authorized for system scope");
            
        case ExecutionScope::kUser:
            // System user requesting user scope - redirect to original UID
            if (current.is_root && current.original_uid.has_value()) {
                return CrossScopeResult::redirect_to_user(
                    "system process executing as user; "
                    "operations will use original UID context");
            }
            return CrossScopeResult::allow("user scope available for any caller");
            
        case ExecutionScope::kSession:
            // Session scope requires valid XDG_RUNTIME_DIR
            if (!current.xdg.runtime_dir.has_value()) {
                return CrossScopeResult::deny(
                    "session scope unavailable; "
                    "$XDG_RUNTIME_DIR not set or inaccessible");
            }
            if (current.is_root) {
                return CrossScopeResult::deny(
                    "session scope invalid for root user");
            }
            return CrossScopeResult::allow("session context validated");
    }
    
    // Unknown scope
    return CrossScopeResult::deny("unknown execution scope requested");
}

// ============================================================================
// Path validation - Is this path valid for the target scope?
// ============================================================================

PathValidationResultDetails validate_path_for_scope(
    const std::filesystem::path& path,
    ExecutionScope target_scope) {
    
    PathValidationResultDetails result;
    result.result = PathValidationResult::kUnknown;
    
    // Normalize path (resolve . and ..)
    auto normalized = std::filesystem::path(path);
    
    switch (target_scope) {
        case ExecutionScope::kSystem: {
            // System paths must start with /usr, /etc, /var/lib/rebuntu, etc.
            static const std::vector<std::string> system_prefixes = {
                "/usr/", "/etc/", "/var/lib/rebuntu", "/var/cache/rebuntu"
            };
            
            auto path_str = normalized.string();
            for (const auto& prefix : system_prefixes) {
                if (path_str.find(prefix) == 0 || 
                    (prefix.size() > 1 && path_str == prefix.substr(0, prefix.size() - 1))) {
                    result.result = PathValidationResult::kValid;
                    return result;
                }
            }
            
            result.result = PathValidationResult::kWrongScope;
            result.expected_scope_path = get_system_bin_path();
            result.explanation = "path does not belong to system scope";
            break;
        }
        
        case ExecutionScope::kUser: {
            // User paths must start with home directory patterns
            const char* home_env = std::getenv("HOME");
            if (home_env) {
                auto home = std::filesystem::path(home_env);
                
                auto path_str = normalized.string();
                if (path_str.find(home.string()) == 0) {
                    result.result = PathValidationResult::kValid;
                    return result;
                }
            }
            
            result.result = PathValidationResult::kWrongScope;
            result.expected_scope_path = get_user_bin_path(
                home_env ? std::filesystem::path(home_env) : std::filesystem::path("/tmp"));
            result.explanation = "path does not belong to user scope";
            break;
        }
        
        case ExecutionScope::kSession: {
            // Session paths should be under XDG_RUNTIME_DIR
            const char* runtime_dir = std::getenv("XDG_RUNTIME_DIR");
            if (runtime_dir) {
                auto rt_path = std::filesystem::path(runtime_dir);
                auto path_str = normalized.string();
                
                if (path_str.find(rt_path.string()) == 0) {
                    result.result = PathValidationResult::kValid;
                    return result;
                }
            }
            
            result.result = PathValidationResult::kWrongScope;
            result.expected_scope_path = std::filesystem::path("/run/user") / 
                std::to_string(getuid());
            result.explanation = "path does not belong to session scope";
            break;
        }
    }
    
    return result;
}

}  // namespace rebuntu::environment::scope