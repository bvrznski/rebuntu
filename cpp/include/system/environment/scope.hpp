// rebuntu::environment::scope — System/User/Session Scope Contract (Phase 2.7)
// Phase 2.14 extension: systemd manager awareness
//
// This establishes Rebuntu's canonical scope model:
//
//   SCOPE     = Execution context boundary (system vs user vs session)
//   DOMAIN    = The "where" of execution (filesystem, systemd, etc.)
//   CONTEXT   = Runtime environment details (XDG dirs, env vars, session state)
//
// Phase 2.14 adds systemd manager awareness:
//   - System vs User vs Session manager distinction
//   - Manager availability detection and status tracking
//   - Unit file path resolution per scope
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/scope.hpp
//
// Phase 2.7 extends Phase 2.4 (privilege) and Phase 2.6 (authorization):
// - Adds explicit Session scope for per-login-session resources
// - Integrates XDG Base Directory specifications
// - Provides explicit override mechanism (--scope=)
// - Defines cross-scope mediation rules
//
// Phase 2.14 extends Phase 2.7:
// - SystemdManagerState: track system vs user manager availability
// - ManagerPathResolver: resolve unit file paths per scope
// - ManagerAdapter: typed interface for systemctl operations
// 
// Core principle: systemd owns process lifecycle; Rebuntu owns semantic
// desired state. Rebuntu may request and observe via adapter, but never
// become a shadow supervisor.

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string_view>
#include <optional>
#include <string>
#include <filesystem>

namespace rebuntu::environment::scope {

// ============================================================================
// XDGBases - XDG Base Directory helpers (defined before struct usage)
// ============================================================================

// XDGBases is defined as a nested struct in ScopeContext

// ============================================================================
// Scope Types - Context boundaries for execution
// ============================================================================

enum class ExecutionScope {
    kSystem,      // System-wide: /usr/bin, /etc/rebuntu, systemd system manager
    kUser,        // Per-user: ~/.local/bin, ~/.config/rebuntu, user systemd manager
    kSession,     // Per-login-session: $XDG_RUNTIME_DIR, session-specific IPC
};

inline std::string_view to_string(ExecutionScope s) {
    switch (s) {
        case ExecutionScope::kSystem: return "system";
        case ExecutionScope::kUser:   return "user";
        case ExecutionScope::kSession: return "session";
    }
    return "unknown";
}

// ============================================================================
// Systemd Manager State - Track system vs user manager availability
// ============================================================================

enum class SystemdManagerStatus {
    kAvailable,       // systemd manager is available and responding
    kUnavailable,     // Manager exists but not accessible (e.g., no user session)
    kUnknown,         // Cannot determine status (acquisition failed)
};

struct SystemdManagerState {
    ExecutionScope scope = ExecutionScope::kSystem;
    
    SystemdManagerStatus status = SystemdManagerStatus::kUnknown;
    
    // Paths to manager-specific unit files
    std::optional<std::filesystem::path> system_unit_path;   // /etc/systemd/system, /usr/lib/systemd/system
    std::optional<std::filesystem::path> user_unit_path;     // ~/.config/systemd/user
    
    // Runtime directory for session scope
    std::optional<std::filesystem::path> runtime_dir;
    
    // Manager identification (for logging/audit)
    bool is_system_manager = false;
    bool is_user_manager = false;
};

// Get systemd manager state for current process
SystemdManagerState discover_systemd_manager_state();

// Check if systemd user manager is available (requires user session)
bool is_user_systemd_manager_available(uid_t uid = 0);

// ============================================================================
// Manager Path Resolver - Resolve unit file paths per scope
// ============================================================================

struct UnitPathInfo {
    std::filesystem::path path;
    bool is_writable = false;   // Can Rebuntu modify this location?
    std::optional<std::string> error_message;  // If not writable
};

// Resolve system manager unit file directory for a scope
UnitPathInfo resolve_system_unit_path();

// Resolve user manager unit file directory for a scope  
UnitPathInfo resolve_user_unit_path(const std::filesystem::path& home);

// Get all possible unit path locations (for reading existing units)
std::vector<std::filesystem::path> get_all_unit_paths(ExecutionScope scope);

// ============================================================================
// ScopeContext - Full context for a scope boundary
// ============================================================================

struct XDGBases {
    std::optional<std::filesystem::path> config_home;
    std::optional<std::filesystem::path> state_home;
    std::optional<std::filesystem::path> cache_home;
    std::optional<std::filesystem::path> data_home;
    std::optional<std::filesystem::path> runtime_dir;
    
    static std::filesystem::path get_user_home();
};

// Convenience functions for default paths
inline std::filesystem::path default_config_home() {
    auto home = XDGBases::get_user_home();
    return home / ".config";
}

inline std::filesystem::path default_state_home() {
    auto home = XDGBases::get_user_home();
    return home / ".local" / "state";
}

inline std::filesystem::path default_cache_home() {
    auto home = XDGBases::get_user_home();
    return home / ".cache";
}

inline std::filesystem::path default_data_home() {
    auto home = XDGBases::get_user_home();
    return home / ".local" / "share";
}

struct ScopeContext {
    ExecutionScope scope = ExecutionScope::kUser;
    
    // Scope-specific paths
    std::optional<std::filesystem::path> bin_path;           // executable location
    std::optional<std::filesystem::path> config_dir;         // configuration storage
    std::optional<std::filesystem::path> state_dir;          // runtime state storage
    std::optional<std::filesystem::path> cache_dir;          // cached data storage
    std::optional<std::filesystem::path> runtime_dir;        // session-specific (kSession only)
    
    // Identity information for scope resolution
    uid_t effective_uid = 0;
    bool is_root = false;
    
    // Audit trail
    std::optional<uid_t> original_uid;   // UID before elevation (sudo)
    std::optional<std::string> sudo_user; // SUDO_USER if elevated
    
    // XDG base directory state
    XDGBases xdg;
    
    // Systemd manager state
    SystemdManagerState systemd_manager;
    
    // Scope override (from command line or explicit request)
    bool has_explicit_scope = false;
};

// ============================================================================
// Scope Resolution API - How do we determine the correct scope?
// ============================================================================

// Discover current process's effective scope from environment and identity
ScopeContext discover_context();

// Build scope context for a specific target UID (not just current process)
ScopeContext discover_context_for_uid(uid_t uid);

// Resolve scope from explicit user request (--scope= flag)
std::optional<ExecutionScope> resolve_explicit_scope(
    const std::string& requested,
    const ScopeContext& current);

// Get default scope based on privilege state
ExecutionScope default_scope_for_privilege(bool is_root);

// ============================================================================
// Scope Path API - Where do things go for each scope?
// ============================================================================

// System-scoped paths (always root-owned, system-wide)
std::filesystem::path get_system_bin_path();
std::filesystem::path get_system_config_dir();
std::filesystem::path get_system_state_dir();
std::filesystem::path get_system_cache_dir();

// User-scoped paths (user-owned, per-user)
std::filesystem::path get_user_bin_path(const std::filesystem::path& home);
std::filesystem::path get_user_config_dir(const std::filesystem::path& home);
std::filesystem::path get_user_state_dir(const std::filesystem::path& home);
std::filesystem::path get_user_cache_dir(const std::filesystem::path& home);

// Session-scoped paths (user-owned, per-session)
std::filesystem::path get_session_runtime_dir(const ScopeContext& ctx);

// ============================================================================
// Scope Mediation API - How do we handle cross-scope requests?
// ============================================================================

enum class CrossScopeAction {
    kAllow,              // Request is valid, proceed normally
    kRequireElevation,   // User requested system operation without privilege
    kRedirectToUser,     // System user tried to access system path as user
    kSessionOnly,        // Operation only valid in session scope
    kDeny,               // Cross-scope operation not permitted
};

struct CrossScopeResult {
    CrossScopeAction action;
    std::string explanation;
    
    static CrossScopeResult allow(std::string msg) {
        return {CrossScopeAction::kAllow, std::move(msg)};
    }
    
    static CrossScopeResult require_elevation(std::string msg) {
        return {CrossScopeAction::kRequireElevation, std::move(msg)};
    }
    
    static CrossScopeResult redirect_to_user(std::string msg) {
        return {CrossScopeAction::kRedirectToUser, std::move(msg)};
    }
    
    static CrossScopeResult session_only(std::string msg) {
        return {CrossScopeAction::kSessionOnly, std::move(msg)};
    }
    
    static CrossScopeResult deny(std::string msg) {
        return {CrossScopeAction::kDeny, std::move(msg)};
    }
};

// Determine what to do when user requests a different scope than current
CrossScopeResult mediate_cross_scope_request(
    const ScopeContext& current,
    ExecutionScope requested);

// ============================================================================
// Scope Verification API - Is this path valid for the current scope?
// ============================================================================

enum class PathValidationResult {
    kValid,           // Path is valid for current scope
    kWrongScope,      // Path belongs to different scope
    kInvalid,         // Path format is invalid
    kUnknown,         // Cannot determine (acquisition failed)
};

struct PathValidationResultDetails {
    PathValidationResult result = PathValidationResult::kUnknown;
    std::optional<std::filesystem::path> expected_scope_path;  // What we expected
    std::string explanation;
    
    bool is_valid() const { return result == PathValidationResult::kValid; }
};

PathValidationResultDetails validate_path_for_scope(
    const std::filesystem::path& path,
    ExecutionScope target_scope);

// ============================================================================
// Error Codes
// ============================================================================

inline constexpr char kErrorScopeMismatch[] = "E_SCOPE_MISMATCH";
inline constexpr char kErrorInvalidScope[] = "E_INVALID_SCOPE";
inline constexpr char kErrorSessionNotFound[] = "E_SESSION_NOT_FOUND";
inline constexpr char kErrorManagerUnavailable[] = "E_MANAGER_UNAVAILABLE";

}  // namespace rebuntu::environment::scope