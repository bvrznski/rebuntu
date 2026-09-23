// rebuntu::environment::sessions — Session & Runtime Identity Implementation (Phase 2.8)
#include <observation/environment/sessions.hpp>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>

namespace rebuntu::environment::sessions {

// ============================================================================
// Session Identity Discovery - Who is this session?
// ============================================================================

SessionIdentity discover_session_identity() {
    SessionIdentity identity;
    
    // Get current process UID
    identity.uid = geteuid();
    
    // Lookup username via NSS
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(identity.uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        identity.username = std::string(result->pw_name);
    }
    
    // Detect invocation context
    identity.invocation_context = detect_invocation_context();
    
    // Detect desktop/session type from environment
    identity.desktop = detect_desktop_environment();
    identity.display_server = detect_display_server();
    
    // Try to get session ID (will fail without D-Bus)
    auto session_id_opt = get_logind_session_id(identity.uid);
    if (session_id_opt) {
        identity.session_id = *session_id_opt;
    }
    
    return identity;
}

SessionIdentity build_session_identity_for_uid(uid_t uid) {
    SessionIdentity identity;
    identity.uid = uid;
    
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        identity.username = std::string(result->pw_name);
    }
    
    return identity;
}

std::optional<uint32_t> get_logind_session_id(uid_t /*uid*/) {
    // Without D-Bus integration (deferred to Phase 38 logind adapter),
    // we cannot reliably get session ID. Return nullopt.
    return std::nullopt;
}

DesktopEnvironment detect_desktop_environment() {
    const char* desktop_session = std::getenv("DESKTOP_SESSION");
    if (desktop_session) {
        std::string ds(desktop_session);
        if (ds.find("gnome") != std::string::npos) return DesktopEnvironment::kGNOME;
        if (ds.find("kde") != std::string::npos || ds.find("plasma") != std::string::npos)
            return DesktopEnvironment::kKDE;
        if (ds.find("xfce") != std::string::npos) return DesktopEnvironment::kXFCE;
        if (ds.find("lxde") != std::string::npos) return DesktopEnvironment::kLXDE;
        if (ds.find("cinnamon") != std::string::npos) return DesktopEnvironment::kCinnamon;
        if (ds.find("mate") != std::string::npos) return DesktopEnvironment::kMate;
        if (ds.find("i3") != std::string::npos) return DesktopEnvironment::ki3;
        if (ds.find("sway") != std::string::npos) return DesktopEnvironment::kSway;
    }
    
    // Check for Wayland session without DE
    const char* wayland_display = std::getenv("WAYLAND_DISPLAY");
    if (wayland_display && *wayland_display) {
        return DesktopEnvironment::kWayland;
    }
    
    return DesktopEnvironment::kNone;
}

DisplayServer detect_display_server() {
    // Check $XDG_SESSION_TYPE first (most reliable)
    const char* session_type = std::getenv("XDG_SESSION_TYPE");
    if (session_type) {
        if (std::string(session_type) == "wayland") return DisplayServer::kWayland;
        if (std::string(session_type) == "x11") return DisplayServer::kX11;
    }
    
    // Check $WAYLAND_DISPLAY
    const char* wayland_display = std::getenv("WAYLAND_DISPLAY");
    if (wayland_display && *wayland_display) {
        return DisplayServer::kWayland;
    }
    
    // Check $DISPLAY
    const char* display = std::getenv("DISPLAY");
    if (display && *display) {
        return DisplayServer::kX11;
    }
    
    return DisplayServer::kNone;
}

// ============================================================================
// Environment Context - How is this process's environment set up?
// ============================================================================

EnvironmentContext build_current_env_context() {
    EnvironmentContext ctx;
    
    // Read environment variables
    const char* home_env = std::getenv("HOME");
    if (home_env && *home_env) ctx.home = std::string(home_env);
    
    const char* user_env = std::getenv("USER");
    if (user_env && *user_env) ctx.user = std::string(user_env);
    
    const char* xdg_runtime = std::getenv("XDG_RUNTIME_DIR");
    if (xdg_runtime && *xdg_runtime) ctx.xdg_runtime_dir = std::string(xdg_runtime);
    
    const char* xdg_config = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config && *xdg_config) ctx.xdg_config_home = std::string(xdg_config);
    
    const char* xdg_state = std::getenv("XDG_STATE_HOME");
    if (xdg_state && *xdg_state) ctx.xdg_state_home = std::string(xdg_state);
    
    const char* xdg_cache = std::getenv("XDG_CACHE_HOME");
    if (xdg_cache && *xdg_cache) ctx.xdg_cache_home = std::string(xdg_cache);
    
    // Detect invocation context
    ctx.invocation_context = detect_invocation_context();
    
    // Check for sudo/SU elevation
    uid_t ruid = getuid();  // Real UID
    uid_t euid = geteuid(); // Effective UID
    
    ctx.original_uid = ruid;
    ctx.is_sudo = (ruid != euid);
    
    // Resolve canonical paths
    if (ctx.home.has_value()) {
        ctx.resolved_home = std::filesystem::path(*ctx.home);
    } else {
        // Fallback to passwd database
        struct passwd pw;
        struct passwd* result = nullptr;
        char buf[4096];
        
        uid_t target_uid = euid;
        if (ctx.is_sudo && ctx.original_uid != 0) {
            target_uid = ctx.original_uid;
        }
        
        if (getpwuid_r(target_uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
            ctx.resolved_home = std::filesystem::path(result->pw_dir);
        }
    }
    
    // Resolve runtime directory
    auto rt_info = discover_runtime_directory();
    ctx.resolved_xdg_runtime_dir = rt_info.path;
    
    return ctx;
}

EnvironmentContext build_env_context_for_uid(uid_t uid, InvocationContext ctx_type) {
    EnvironmentContext ctx;
    
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        ctx.home = std::string(result->pw_dir);
        ctx.user = std::string(result->pw_name);
        
        // Fallback paths
        ctx.xdg_config_home = pw.pw_dir + std::string("/.config");
        ctx.xdg_state_home = pw.pw_dir + std::string("/.local/state");
        ctx.xdg_cache_home = pw.pw_dir + std::string("/.cache");
    }
    
    // Set runtime directory (systemd user manager creates this)
    if (uid != 0) {
        ctx.xdg_runtime_dir = "/run/user/" + std::to_string(uid);
    }
    
    ctx.invocation_context = ctx_type;
    ctx.original_uid = uid;
    ctx.is_sudo = false;  // Not elevated when explicitly targeting UID
    
    if (ctx.home.has_value()) {
        ctx.resolved_home = std::filesystem::path(*ctx.home);
    }
    
    return ctx;
}

std::filesystem::path get_canonical_home(const EnvironmentContext& ctx) {
    if (ctx.is_sudo && ctx.original_uid != 0) {
        // Running under sudo - use original user's home
        struct passwd pw;
        struct passwd* result = nullptr;
        char buf[4096];
        
        if (getpwuid_r(ctx.original_uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
            return std::filesystem::path(result->pw_dir);
        }
    }
    
    // Normal case: use HOME from context
    if (ctx.home.has_value()) {
        return std::filesystem::path(*ctx.home);
    }
    
    // Last resort: use current process's home
    const char* home_env = std::getenv("HOME");
    if (home_env && *home_env) {
        return std::filesystem::path(home_env);
    }
    
    return std::filesystem::path();  // Unknown
}

std::filesystem::path get_runtime_dir(const EnvironmentContext& ctx) {
    if (ctx.xdg_runtime_dir.has_value()) {
        return std::filesystem::path(*ctx.xdg_runtime_dir);
    }
    
    // Fallback to /run/user/<uid> for non-root
    if (ctx.original_uid != 0 && 
        ctx.original_uid != std::numeric_limits<uid_t>::max()) {
        return std::filesystem::path("/run/user") / std::to_string(ctx.original_uid);
    }
    
    return std::filesystem::path();  // No runtime directory available
}

// ============================================================================
// Environment Inheritance Rules - Which env vars to trust?
// ============================================================================

EnvVarPolicy get_env_var_policy(const std::string& name, const EnvironmentContext& ctx) {
    // HOME - always override with canonical value when elevated
    if (name == "HOME") {
        return ctx.is_sudo ? EnvVarPolicy::kOverride : EnvVarPolicy::kTrust;
    }
    
    // USER - always use canonical username from passwd database
    if (name == "USER") {
        return EnvVarPolicy::kOverride;
    }
    
    // XDG_RUNTIME_DIR - trust when available, otherwise error
    if (name == "XDG_RUNTIME_DIR") {
        if (!ctx.xdg_runtime_dir.has_value()) {
            return EnvVarPolicy::kWarn;  // Missing runtime dir in user session
        }
        return EnvVarPolicy::kTrust;
    }
    
    // XDG_*_HOME variables - use from context with fallbacks
    if (name.find("XDG_") == 0 && name.find("_HOME") != std::string::npos) {
        return ctx.is_sudo ? EnvVarPolicy::kWarn : EnvVarPolicy::kTrust;
    }
    
    // For other variables, trust the environment but warn for systemd contexts
    if (ctx.invocation_context == InvocationContext::kSystemdService ||
        ctx.invocation_context == InvocationContext::kSystemdTimer) {
        return EnvVarPolicy::kWarn;  // systemd may have incomplete env
    }
    
    return EnvVarPolicy::kTrust;
}

std::filesystem::path resolve_canonical_home(
    const EnvironmentContext& ctx,
    uid_t target_uid) {
    
    struct passwd pw;
    struct passwd* result = nullptr;
    char buf[4096];
    
    if (getpwuid_r(target_uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
        return std::filesystem::path(result->pw_dir);
    }
    
    return std::filesystem::path();  // Unknown
}

// ============================================================================
// Session State Provider API - Track active sessions
// ============================================================================

std::vector<SessionRecord> get_user_sessions(uid_t /*uid*/) {
    // Without D-Bus integration (deferred to Phase 38 logind adapter),
    // we cannot query active sessions. Return empty vector.
    return {};
}

std::optional<SessionRecord> get_primary_session(uid_t /*uid*/) {
    // Without D-Bus integration, return nullopt
    return std::nullopt;
}

// ============================================================================
// Runtime Directory API - Session-scoped IPC and temp files
// ============================================================================

RuntimeDirectoryInfo discover_runtime_directory() {
    RuntimeDirectoryInfo info;
    
    const char* runtime_dir = std::getenv("XDG_RUNTIME_DIR");
    if (!runtime_dir || !*runtime_dir) {
        info.status = RuntimeDirStatus::kUnavailable;
        return info;
    }
    
    info.path = std::filesystem::path(runtime_dir);
    
    // Check if directory exists and is accessible
    std::error_code ec;
    if (!std::filesystem::exists(info.path, ec)) {
        info.status = RuntimeDirStatus::kUnavailable;
        return info;
    }
    
    // Verify ownership (should be owned by current user)
    struct stat st;
    if (stat(info.path.string().c_str(), &st) == 0) {
        uid_t euid = geteuid();
        if (st.st_uid != euid) {
            info.status = RuntimeDirStatus::kPermissionError;
            return info;
        }
        
        // Check permissions (should be 0700 or more restrictive)
        mode_t mode = st.st_mode & 0777;
        if ((mode & 0077) != 0) {
            info.status = RuntimeDirStatus::kPermissionError;
            return info;
        }
    }
    
    info.status = RuntimeDirStatus::kAvailable;
    return info;
}

RuntimeDirectoryInfo get_runtime_directory_for_uid(uid_t uid) {
    if (uid == 0) {
        // Root doesn't have a user runtime directory
        return {};
    }
    
    RuntimeDirectoryInfo info;
    info.path = std::filesystem::path("/run/user") / std::to_string(uid);
    
    std::error_code ec;
    if (!std::filesystem::exists(info.path, ec)) {
        info.status = RuntimeDirStatus::kUnavailable;
        return info;
    }
    
    // Note: We cannot verify ownership without elevated privileges
    info.status = RuntimeDirStatus::kAvailable;
    return info;
}

bool ensure_runtime_directory(const EnvironmentContext& /*ctx*/, std::filesystem::path* out_path) {
    // For now, we rely on systemd user manager or the environment to provide
    // XDG_RUNTIME_DIR. Directories under /run are typically created automatically.
    
    if (out_path) {
        auto rt_info = discover_runtime_directory();
        if (rt_info.is_valid()) {
            *out_path = rt_info.path;
            return true;
        }
    }
    
    return false;
}

// ============================================================================
// Invocation Context Detection - How was this process started?
// ============================================================================

InvocationContext detect_invocation_context() {
    // Check for systemd service first
    const char* systemd_notify = std::getenv("NOTIFY_SOCKET");
    if (systemd_notify && *systemd_notify) {
        return InvocationContext::kSystemdService;
    }
    
    // Check for systemd timer
    const char* systemd_timer = std::getenv("SYSTEMD_TIMER_MONOTONIC_USEC");
    if (systemd_timer && *systemd_timer) {
        return InvocationContext::kSystemdTimer;
    }
    
    // Check for cron
    const char* cron_env = std::getenv("LOGNAME");
    if (!cron_env || !*cron_env) {
        const char* path = std::getenv("_");
        if (path && std::string(path).find("/cron") != std::string::npos) {
            return InvocationContext::kCron;
        }
    }
    
    // Check for sudo
    const char* sudo_user = std::getenv("SUDO_USER");
    if (sudo_user && *sudo_user) {
        return InvocationContext::kSudo;
    }
    
    // Check for su
    const char* su_user = std::getenv("SU_FROM");
    if (su_user && *su_user) {
        return InvocationContext::kSU;
    }
    
    // Check for SSH
    const char* ssh_client = std::getenv("SSH_CLIENT");
    const char* ssh_connection = std::getenv("SSH_CONNECTION");
    if ((ssh_client && *ssh_client) || (ssh_connection && *ssh_connection)) {
        return InvocationContext::kSSH;
    }
    
    // Check for container
    const char* container = std::getenv("container");
    if (container && *container) {
        return InvocationContext::kContainer;
    }
    
    // Direct execution (shell, desktop launch)
    return InvocationContext::kDirect;
}

bool is_systemd_service() {
    const char* systemd_notify = std::getenv("NOTIFY_SOCKET");
    return systemd_notify && *systemd_notify;
}

bool is_running_under_sudo(uid_t* original_uid) {
    const char* sudo_user = std::getenv("SUDO_USER");
    
    if (sudo_user && *sudo_user) {
        if (original_uid) {
            // Try to get the original UID from SUDO_USER
            struct passwd pw;
            struct passwd* result = nullptr;
            char buf[4096];
            
            if (getpwnam_r(sudo_user, &pw, buf, sizeof(buf), &result) == 0 && result) {
                *original_uid = result->pw_uid;
            } else {
                // Fallback: getuid returns real UID which may be non-zero
                *original_uid = getuid();
            }
        }
        return true;
    }
    
    // Also check for effective != real UID
    uid_t ruid = getuid();
    uid_t euid = geteuid();
    if (ruid != 0 && euid == 0) {
        if (original_uid) *original_uid = ruid;
        return true;
    }
    
    return false;
}

bool is_running_via_ssh() {
    const char* ssh_client = std::getenv("SSH_CLIENT");
    const char* ssh_connection = std::getenv("SSH_CONNECTION");
    return (ssh_client && *ssh_client) || (ssh_connection && *ssh_connection);
}

}  // namespace rebuntu::environment::sessions