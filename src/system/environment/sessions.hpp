// rebuntu::environment::sessions — Session & Runtime Identity (Phase 2.8)
//
// This module provides session identity management, runtime directory discovery,
// and environment inheritance handling for different invocation contexts:
//   - Login sessions (logind/systemd-user manager)
//   - Desktop sessions (X11/Wayland/TTY)
//   - Process invocation contexts (systemd, sudo, SSH, TTY)
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/sessions.hpp
//
// Phase 2.8 extends Phase 2.7 (scope):
// - Adds explicit session identity distinct from user identity
// - Provides session lifetime tracking
// - Defines environment inheritance rules for different invocation contexts

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <cstdint>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <chrono>
#include <filesystem>

namespace rebuntu::environment::sessions {

// ============================================================================
// Session Types - Context boundaries for identity
// ============================================================================

enum class SessionType {
    kLogin,        // Login session (systemd-logind managed)
    kDesktop,      // Desktop session (X11/Wayland)
    kShell,        // Interactive shell session (TTY/SSH)
    kSystemdUser,  // systemd --user manager session
    kBackground,   // Non-interactive background process
};

inline std::string_view to_string(SessionType t) {
    switch (t) {
        case SessionType::kLogin:      return "login";
        case SessionType::kDesktop:    return "desktop";
        case SessionType::kShell:      return "shell";
        case SessionType::kSystemdUser:return "systemd-user";
        case SessionType::kBackground: return "background";
    }
    return "unknown";
}

// ============================================================================
// Desktop Environment Types
// ============================================================================

enum class DesktopEnvironment {
    kNone,
    kGNOME,
    kKDE,
    kXFCE,
    kLXDE,
    kCinnamon,
    kMate,
    ki3,
    kSway,
    kWayland,      // Wayland session without specific DE
    kUnknown,
};

inline std::string_view to_string(DesktopEnvironment de) {
    switch (de) {
        case DesktopEnvironment::kNone:      return "none";
        case DesktopEnvironment::kGNOME:     return "gnome";
        case DesktopEnvironment::kKDE:       return "kde";
        case DesktopEnvironment::kXFCE:      return "xfce";
        case DesktopEnvironment::kLXDE:      return "lxde";
        case DesktopEnvironment::kCinnamon:  return "cinnamon";
        case DesktopEnvironment::kMate:      return "mate";
        case DesktopEnvironment::ki3:        return "i3";
        case DesktopEnvironment::kSway:      return "sway";
        case DesktopEnvironment::kWayland:   return "wayland";
        default:                             return "unknown";
    }
}

// ============================================================================
// Display Server Types
// ============================================================================

enum class DisplayServer {
    kNone,
    kX11,
    kWayland,
    kUnknown,
};

inline std::string_view to_string(DisplayServer ds) {
    switch (ds) {
        case DisplayServer::kNone:     return "none";
        case DisplayServer::kX11:      return "x11";
        case DisplayServer::kWayland:  return "wayland";
        default:                       return "unknown";
    }
}

// ============================================================================
// Invocation Context - How was this process started?
// ============================================================================

enum class InvocationContext {
    kDirect,           // Direct shell execution
    kSudo,             // Started via sudo (with elevation)
    kSU,               // Started via su (without full login)
    kSSH,              // Started via SSH
    kSystemdService,   // Started by systemd service unit
    kSystemdTimer,     // Started by systemd timer
    kCron,             // Started by cron/at
    kDesktopLaunch,    // Launched from desktop environment
    kContainer,        // Running inside a container
};

inline std::string_view to_string(InvocationContext ctx) {
    switch (ctx) {
        case InvocationContext::kDirect:       return "direct";
        case InvocationContext::kSudo:         return "sudo";
        case InvocationContext::kSU:           return "su";
        case InvocationContext::kSSH:          return "ssh";
        case InvocationContext::kSystemdService:return "systemd-service";
        case InvocationContext::kSystemdTimer: return "systemd-timer";
        case InvocationContext::kCron:         return "cron";
        case InvocationContext::kDesktopLaunch:return "desktop-launch";
        case InvocationContext::kContainer:    return "container";
    }
    return "unknown";
}

// ============================================================================
// Session Identity - Distinguish login session from user account
// ============================================================================

struct SessionIdentity {
    // User identity (who)
    uid_t uid = 0;
    std::optional<std::string> username;
    
    // Session identity (which login session)
    std::optional<uint32_t> session_id;      // logind session ID
    std::optional<std::string> session_name; // e.g., "tty1", "wayland-1"
    
    // Session metadata
    SessionType type = SessionType::kBackground;
    DesktopEnvironment desktop = DesktopEnvironment::kUnknown;
    DisplayServer display_server = DisplayServer::kNone;
    
    // Authentication state
    bool authenticated = false;
    
    // Invocation context (how this process was started)
    InvocationContext invocation_context = InvocationContext::kDirect;
};

// ============================================================================
// Environment Context - How environment variables are inherited
// ============================================================================

struct EnvironmentContext {
    // Current process's environment state
    std::optional<std::string> home;           // $HOME
    std::optional<std::string> user;           // $USER
    std::optional<std::string> xdg_runtime_dir;// $XDG_RUNTIME_DIR
    std::optional<std::string> xdg_config_home;// $XDG_CONFIG_HOME
    std::optional<std::string> xdg_state_home; // $XDG_STATE_HOME
    std::optional<std::string> xdg_cache_home; // $XDG_CACHE_HOME
    
    // Session environment (from logind/systemd-user)
    std::optional<std::string> session_type;   // "wayland", "x11", "tty"
    
    // Context information
    InvocationContext invocation_context = InvocationContext::kDirect;
    bool is_sudo = false;
    
    uid_t original_uid = 0;  // Before elevation (0 means not elevated or unknown)
    
    // Derived canonical paths
    std::filesystem::path resolved_home;
    std::filesystem::path resolved_xdg_runtime_dir;
};

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorSessionNotFound[] = "E_SESSION_NOT_FOUND";
inline constexpr char kErrorRuntimeDirMissing[] = "E_RUNTIME_DIR_MISSING";
inline constexpr char kErrorEnvironmentInconsistent[] = "E_ENVIRONMENT_INCONSISTENT";

// ============================================================================
// Session Identity API - Who is this session?
// ============================================================================

// Discover current process's session identity
SessionIdentity discover_session_identity();

// Build session identity for a specific UID (not just current)
SessionIdentity build_session_identity_for_uid(uid_t uid);

// Get the logind session ID for a user (if available via D-Bus)
std::optional<uint32_t> get_logind_session_id(uid_t uid);

// Detect desktop environment from environment variables
DesktopEnvironment detect_desktop_environment();

// Detect display server in use
DisplayServer detect_display_server();

// ============================================================================
// Environment Context API - How is this process's environment set up?
// ============================================================================

// Build environment context for current process
EnvironmentContext build_current_env_context();

// Build environment context for a specific UID/context
EnvironmentContext build_env_context_for_uid(uid_t uid, InvocationContext ctx);

// Get canonical home directory (respects sudo/SU context)
std::filesystem::path get_canonical_home(const EnvironmentContext& ctx);

// Get runtime directory with proper scope handling
std::filesystem::path get_runtime_dir(const EnvironmentContext& ctx);

// ============================================================================
// Environment Inheritance Rules - Which env vars to trust?
// ============================================================================

enum class EnvVarPolicy {
    kTrust,       // Use the environment variable value
    kWarn,        // Use but log a warning (possibly inconsistent)
    kIgnore,      // Ignore this variable entirely
    kOverride,    // Override with canonical value
};

// Determine how to handle an environment variable based on context
EnvVarPolicy get_env_var_policy(const std::string& name, const EnvironmentContext& ctx);

// Get canonical HOME for the given context (respects sudo/SU)
std::filesystem::path resolve_canonical_home(
    const EnvironmentContext& ctx,
    uid_t target_uid);

// ============================================================================
// Session State Provider API - Track active sessions
// ============================================================================

enum class SessionState {
    kActive,      // Session is currently logged in
    kInactive,    // Session exists but is not active (locked/screen blanked)
    kPending,     // Session is being created
    kClosing,     // Session is being torn down
    kUnknown,
};

inline std::string_view to_string(SessionState s) {
    switch (s) {
        case SessionState::kActive:   return "active";
        case SessionState::kInactive: return "inactive";
        case SessionState::kPending:  return "pending";
        case SessionState::kClosing:  return "closing";
        default:                      return "unknown";
    }
}

struct SessionRecord {
    uint32_t session_id = 0;
    uid_t uid = 0;
    std::string username;
    
    std::string seat_id;              // e.g., "seat0"
    std::string session_type;         // "wayland", "x11", "tty"
    
    SessionType session_type_enum = SessionType::kBackground;
    SessionState state = SessionState::kUnknown;
    
    std::chrono::system_clock::time_point active_since;
    bool is_local = false;            // Connected locally (not SSH)
    bool is_graphical = false;        // Has display server
};

// Get all active sessions for a user
std::vector<SessionRecord> get_user_sessions(uid_t uid);

// Get the primary active session for a user
std::optional<SessionRecord> get_primary_session(uid_t uid);

// ============================================================================
// Runtime Directory API - Session-scoped IPC and temp files
// ============================================================================

enum class RuntimeDirStatus {
    kAvailable,       // $XDG_RUNTIME_DIR exists and is accessible
    kUnavailable,     // Environment variable not set or directory missing
    kPermissionError, // Exists but not accessible (wrong permissions)
    kUnknown,
};

struct RuntimeDirectoryInfo {
    std::filesystem::path path;
    RuntimeDirStatus status = RuntimeDirStatus::kUnknown;
    
    bool is_valid() const { return status == RuntimeDirStatus::kAvailable; }
};

// Discover runtime directory for current process
RuntimeDirectoryInfo discover_runtime_directory();

// Discover runtime directory for a specific UID
RuntimeDirectoryInfo get_runtime_directory_for_uid(uid_t uid);

// Create session-scoped runtime directory (if needed)
bool ensure_runtime_directory(const EnvironmentContext& ctx, std::filesystem::path* out_path = nullptr);

// ============================================================================
// Invocation Context Detection - How was this process started?
// ============================================================================

// Detect the invocation context from environment variables and state
InvocationContext detect_invocation_context();

// Check if running under systemd service unit
bool is_systemd_service();

// Check if running under sudo with elevation
bool is_running_under_sudo(uid_t* original_uid = nullptr);

// Check if running via SSH
bool is_running_via_ssh();

}  // namespace rebuntu::environment::sessions