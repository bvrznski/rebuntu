// rebuntu::adapters::session::utmp — Utmp/Wtmp/Btmp Session Observation Adapter (Phase 5.27)
//
// This module implements Rebuntu's native session observation through Linux utmp/wtmp/btmp:
//   - Reads current sessions from /var/run/utmp
//   - Reads login history from /var/log/wtmp
//   - Reads failed login attempts from /var/log/btmp
//   - Uses getutent/getutid family functions for utmp access
//
// Native Interfaces Used:
//   - /var/run/utmp — Current user sessions (utmp file)
//   - /var/log/wtmp — Login history (wtmp file)
//   - /var/log/btmp — Failed login attempts (btmp file)
//   - getutent(), getutid(), getutuser() — utmp entry iteration and lookup
//
// Key Distinctions:
//   - Session = User + Terminal + Time Window (not the same as user identity)
//   - Utmp = current sessions, Wtmp = login history, Btmp = failed logins
//   - SessionIdentity = uid + terminal + session_start for durable identification
//   - No authentication inference: session presence does not imply authorized access

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>

namespace rebuntu::adapters::session::utmp {

// ============================================================================
// SessionType — How was this session established?
// ============================================================================

enum class SessionType {
    kUnknown,        // Type unknown (cannot determine)
    kLogin,          // Traditional login via getty/login
    kDesktop,        // Desktop environment session
    kRemote,         // Remote connection (SSH, telnet, etc.)
    kSystemdUser,    // systemd --user manager session
    kContainer,      // Container session
};

inline std::string to_string(SessionType t) {
    switch (t) {
        case SessionType::kUnknown:     return "unknown";
        case SessionType::kLogin:       return "login";
        case SessionType::kDesktop:     return "desktop";
        case SessionType::kRemote:      return "remote";
        case SessionType::kSystemdUser: return "systemd-user";
        case SessionType::kContainer:   return "container";
    }
    return "unknown";
}

// ============================================================================
// LoginType — Type of login that created the session
// ============================================================================

enum class LoginType {
    kUnknown,        // Unknown login type
    kNormal,         // Normal login (getty/login)
    kKilled,         // Session killed
    kDead,           // Dead session entry
    kOldTime,        // Time change (old time)
    kNewTime,        // Time change (new time)
    kInitProcess,    // Process started by init
    kLoginProcess,   // Login process (pid 1)
    kUserProcess,    // User process
    kReboot,         // System reboot
    kShutdown,       // System shutdown
};

inline std::string to_string(LoginType t) {
    switch (t) {
        case LoginType::kUnknown:      return "unknown";
        case LoginType::kNormal:       return "normal";
        case LoginType::kKilled:       return "killed";
        case LoginType::kDead:         return "dead";
        case LoginType::kOldTime:      return "old-time";
        case LoginType::kNewTime:      return "new-time";
        case LoginType::kInitProcess:  return "init-process";
        case LoginType::kLoginProcess: return "login-process";
        case LoginType::kUserProcess:  return "user-process";
        case LoginType::kReboot:       return "reboot";
        case LoginType::kShutdown:     return "shutdown";
    }
    return "unknown";
}

// ============================================================================
// SessionIdentity — Stable identity for a session
//
// A session is uniquely identified by the combination of:
//   - uid: User ID who owns this session
//   - terminal: TTY/PTS device (e.g., "/dev/tty1", "/dev/pts/0")
//   - start_time: When the session started
//
// This combination ensures sessions can be tracked even if PIDs change.
// ============================================================================

struct SessionIdentity {
    uid_t uid{0};                                    // User ID
    std::string terminal;                            // Terminal device path
    
    std::chrono::system_clock::time_point start_time; // Session start time
    
    bool is_valid() const {
        return !terminal.empty() && start_time.time_since_epoch().count() > 0;
    }
};

inline bool operator==(const SessionIdentity& a, const SessionIdentity& b) {
    return a.uid == b.uid &&
           a.terminal == b.terminal &&
           a.start_time == b.start_time;
}

inline bool operator!=(const SessionIdentity& a, const SessionIdentity& b) {
    return !(a == b);
}

// ============================================================================
// UtmpEntry — Raw utmp entry from /var/run/utmp
//
// This represents a single session record from the utmp file.
// ============================================================================

struct UtmpEntry {
    LoginType type{LoginType::kUnknown};
    
    std::string terminal;       // e.g., "/dev/tty1", "/dev/pts/0"
    pid_t pid{-1};              // Process ID for this session
    
    uid_t uid{0};               // User ID
    std::optional<std::string> username;
    
    std::string hostname;       // Remote hostname (for remote sessions)
    std::optional<std::string> line;   // Term name (short terminal name)
    std::optional<std::string> id;     // Inittab ID
    std::optional<std::string> session_id; // Session ID
    
    // Time information
    std::chrono::system_clock::time_point entry_time;
    
    // Session metadata
    SessionType session_type{SessionType::kUnknown};
    bool is_remote{false};      // SSH/telnet connection
    bool is_graphical{false};   // Desktop environment session
    
    // Derived state
    std::optional<std::string> display;          // $DISPLAY value if available
    std::optional<std::string> xdg_session_type; // $XDG_SESSION_TYPE if available
    std::optional<std::string> display_server;   // "x11" or "wayland"
};

// ============================================================================
// SessionRecord — Processed session record with context
//
// This is the normalized form of a session, including derived metadata.
// ============================================================================

struct SessionRecord {
    SessionIdentity identity;
    
    std::string username;
    uid_t uid{0};
    
    // Terminal info
    std::string terminal;       // e.g., "/dev/tty1"
    std::optional<std::string> display_server;  // "x11" or "wayland"
    
    // Time info
    std::chrono::system_clock::time_point start_time;
    std::chrono::seconds session_duration{0};   // Time elapsed since start
    
    // Session type and context
    SessionType type{SessionType::kUnknown};
    LoginType login_type{LoginType::kNormal};
    
    bool is_active{true};       // Currently logged in
    bool is_local{true};        // Local (not remote)
    bool is_graphical{false};   // Has display server
    
    // Derived state
    std::optional<std::string> source;  // "utmp" for current, "wtmp" for history
};

// ============================================================================
// FailedLoginRecord — Record from /var/log/btmp
//
// Represents a failed login attempt.
// ============================================================================

struct FailedLoginRecord {
    LoginType type{LoginType::kUnknown};
    
    std::string terminal;       // Terminal used for login attempt
    std::chrono::system_clock::time_point timestamp;
    
    uid_t uid{0};
    std::optional<std::string> username;
    
    std::string hostname;       // Remote host (if applicable)
    std::optional<int> line;    // Line number (for terminal-based auth)
    std::optional<std::string> reason;  // Reason for failure if known
};

// ============================================================================
// SessionObservationResult — Result of session observation
//
// Contains all observed sessions with statistics and provenance.
// ============================================================================

struct SessionObservationResult {
    rebuntu::core::SemanticStatus status{rebuntu::core::SemanticStatus::kUnknown};
    std::string description;
    
    // All currently active sessions
    std::vector<SessionRecord> current_sessions;
    
    // Statistics
    size_t total_sessions{0};
    size_t local_sessions{0};
    size_t remote_sessions{0};
    size_t graphical_sessions{0};
    std::unordered_map<std::string, size_t> sessions_by_user;  // username -> count
    
    // Timing
    std::chrono::system_clock::time_point observed_at;
    std::chrono::milliseconds elapsed_ms{0};
    
    // Provider provenance
    std::string source{"utmp/wtmp"};  // Source of observations
    
    // Errors encountered (non-fatal)
    std::vector<std::pair<size_t, std::string>> errors;  // index -> error message
    
    std::optional<rebuntu::core::Error> fatal_error;
};

// ============================================================================
// UtmpAdapter — Interface for utmp/wtmp/btmp session observation
//
// Provides bounded, cancellable, freshness-aware session observation:
//   - observe_current_sessions: Get all currently logged-in users/sessions
//   - get_login_history: Get login records from wtmp
//   - get_failed_logins: Get failed login attempts from btmp
// ============================================================================

class UtmpAdapter {
public:
    virtual ~UtmpAdapter() = default;
    
    // Observe all currently active sessions
    // Returns observations sorted by session start time for deterministic iteration
    virtual SessionObservationResult observe_current_sessions() = 0;
    
    // Get login history from wtmp file (limited to recent entries)
    // Returns records sorted by timestamp (most recent first)
    virtual std::vector<SessionRecord> get_login_history(size_t max_records = 100) = 0;
    
    // Get failed login attempts from btmp file
    // Returns records sorted by timestamp (most recent first)
    virtual std::vector<FailedLoginRecord> get_failed_logins(size_t max_records = 50) = 0;
    
    // Get sessions for a specific user (current and historical)
    virtual std::vector<SessionRecord> get_user_sessions(uid_t uid, size_t max_records = 100) = 0;
    
    // Get freshness information about the last observation
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from files
    virtual SessionObservationResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<UtmpAdapter> make_utmp_adapter();

}  // namespace rebuntu::adapters::session::utmp
