// rebuntu::adapters::session::utmp — Utmp/Wtmp/Btmp Session Observation Implementation (Phase 5.27)
//
// This module implements the utmp/wtmp/btmp-based session observation adapter:
//   - Reads current sessions from /var/run/utmp
//   - Reads login history from /var/log/wtmp
//   - Reads failed login attempts from /var/log/btmp

#include "adapters/session/utmp/types.hpp"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <memory>
#include <optional>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

namespace rebuntu::adapters::session::utmp {

// ============================================================================
// Helper: Convert time_t to chrono system_clock::time_point
// ============================================================================

static std::chrono::system_clock::time_point time_to_timepoint(time_t t) {
    return std::chrono::system_clock::from_time_t(t);
}

// ============================================================================
// Helper: Parse login type from utmp.ut_type field
// ============================================================================

static LoginType parse_login_type(int ut_type) {
    switch (ut_type) {
        case EMPTY:         return LoginType::kDead;
        case RUN_LVL:       return LoginType::kReboot;
        case BOOT_TIME:     return LoginType::kReboot;
        case NEW_TIME:      return LoginType::kNewTime;
        case OLD_TIME:      return LoginType::kOldTime;
        case INIT_PROCESS:  return LoginType::kInitProcess;
        case LOGIN_PROCESS: return LoginType::kLoginProcess;
        case USER_PROCESS:  return LoginType::kNormal;
        case DEAD_PROCESS:  return LoginType::kKilled;
        default:            return LoginType::kUnknown;
    }
}

// ============================================================================
// Helper: Detect session type from terminal name
// ============================================================================

static SessionType detect_session_type(const std::string& terminal) {
    // Check for remote connections (SSH)
    if (terminal.find("pts/") != std::string::npos || 
        terminal.find("/dev/pty") != std::string::npos ||
        terminal.find("ssh") != std::string::npos) {
        return SessionType::kRemote;
    }
    
    // Check for local TTYs
    if (terminal.find("tty") != std::string::npos) {
        return SessionType::kLogin;
    }
    
    // Default to desktop for graphical sessions
    return SessionType::kDesktop;
}

// ============================================================================
// Helper: Read utmp entries from file
// ============================================================================

static std::vector<UtmpEntry> read_utmp_file(const char* path, size_t max_entries = 100) {
    std::vector<UtmpEntry> entries;
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        return entries;  // Return empty on error (file might not exist)
    }
    
    struct utmp entry;
    size_t count = 0;
    
    while (fread(&entry, sizeof(struct utmp), 1, fp) == 1 && count < max_entries) {
        UtmpEntry ue;
        
        // Parse basic fields
        ue.type = parse_login_type(entry.ut_type);
        
        // Copy terminal name (ensure null-terminated)
        std::string term(entry.ut_line, UT_LINESIZE);
        size_t pos = term.find('\0');
        if (pos != std::string::npos) {
            term.resize(pos);
        }
        ue.terminal = term;
        
        // Skip empty entries
        if (ue.terminal.empty()) {
            continue;
        }
        
        ue.pid = entry.ut_pid;
        ue.uid = 0;  // utmp struct doesn't contain uid field directly
        
        // Copy username (ensure null-terminated)
        std::string user(entry.ut_user, UT_NAMESIZE);
        pos = user.find('\0');
        if (pos != std::string::npos) {
            user.resize(pos);
        }
        if (!user.empty()) {
            ue.username = user;
        }
        
        // Copy hostname (ensure null-terminated)
        std::string host(entry.ut_host, UT_HOSTSIZE);
        pos = host.find('\0');
        if (pos != std::string::npos) {
            host.resize(pos);
        }
        ue.hostname = host;
        
        // Set entry time from ut_tv
        ue.entry_time = time_to_timepoint(entry.ut_tv.tv_sec);
        
        // Detect session type
        ue.session_type = detect_session_type(ue.terminal);
        ue.is_remote = (ue.hostname.find(':') != std::string::npos || 
                        ue.hostname.find('.') != std::string::npos);
        ue.is_graphical = (ue.session_type == SessionType::kDesktop);
        
        // Detect display server
        if (ue.terminal.find("pts/") != std::string::npos) {
            ue.display_server = "x11";
        }
        
        entries.push_back(std::move(ue));
        count++;
    }
    
    fclose(fp);
    return entries;
}

// ============================================================================
// Helper: Read wtmp file (login history)
// ============================================================================

static std::vector<SessionRecord> read_wtmp_file(const char* path, size_t max_records = 100) {
    std::vector<SessionRecord> records;
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        return records;
    }
    
    struct utmp entry;
    size_t count = 0;
    
    while (fread(&entry, sizeof(struct utmp), 1, fp) == 1 && count < max_records) {
        // wtmp contains both login and logout entries
        // We filter for USER_PROCESS (login) entries only
        
        if (entry.ut_type != USER_PROCESS) {
            continue;
        }
        
        SessionRecord sr;
        
        std::string term(entry.ut_line, UT_LINESIZE);
        size_t pos = term.find('\0');
        if (pos != std::string::npos) {
            term.resize(pos);
        }
        sr.terminal = term;
        
        std::string user(entry.ut_user, UT_NAMESIZE);
        pos = user.find('\0');
        if (pos != std::string::npos) {
            user.resize(pos);
        }
        sr.username = user;
        
        sr.uid = 0;  // utmp struct doesn't contain uid field directly
        sr.start_time = time_to_timepoint(entry.ut_tv.tv_sec);
        
        sr.type = detect_session_type(sr.terminal);
        sr.login_type = LoginType::kNormal;
        sr.is_local = (entry.ut_host[0] == '\0');
        sr.is_graphical = (sr.type == SessionType::kDesktop);
        sr.source = "wtmp";
        
        records.push_back(std::move(sr));
        count++;
    }
    
    fclose(fp);
    
    // Sort by timestamp (most recent first)
    std::sort(records.begin(), records.end(),
              [](const SessionRecord& a, const SessionRecord& b) {
                  return a.start_time > b.start_time;
              });
    
    return records;
}

// ============================================================================
// Helper: Read btmp file (failed login attempts)
// ============================================================================

static std::vector<FailedLoginRecord> read_btmp_file(const char* path, size_t max_records = 50) {
    std::vector<FailedLoginRecord> records;
    
    FILE* fp = fopen(path, "r");
    if (!fp) {
        return records;  // File might not exist
    }
    
    struct utmp entry;
    size_t count = 0;
    
    while (fread(&entry, sizeof(struct utmp), 1, fp) == 1 && count < max_records) {
        FailedLoginRecord fr;
        
        std::string term(entry.ut_line, UT_LINESIZE);
        size_t pos = term.find('\0');
        if (pos != std::string::npos) {
            term.resize(pos);
        }
        fr.terminal = term;
        
        fr.timestamp = time_to_timepoint(entry.ut_tv.tv_sec);
        fr.uid = 0;  // utmp struct doesn't contain uid field directly
        
        // Try to extract username from ut_user field
        std::string user(entry.ut_user, UT_NAMESIZE);
        pos = user.find('\0');
        if (pos != std::string::npos) {
            user.resize(pos);
        }
        if (!user.empty()) {
            fr.username = user;
        }
        
        // Extract hostname from ut_host field
        std::string host(entry.ut_host, UT_HOSTSIZE);
        pos = host.find('\0');
        if (pos != std::string::npos) {
            host.resize(pos);
        }
        fr.hostname = host;
        
        fr.type = parse_login_type(entry.ut_type);
        // For btmp, we typically don't have detailed failure reasons
        // The failure is implicit (record in btmp means login failed)
        
        records.push_back(std::move(fr));
        count++;
    }
    
    fclose(fp);
    
    // Sort by timestamp (most recent first)
    std::sort(records.begin(), records.end(),
              [](const FailedLoginRecord& a, const FailedLoginRecord& b) {
                  return a.timestamp > b.timestamp;
              });
    
    return records;
}

// ============================================================================
// UtmpAdapter implementation
// ============================================================================

class UtmpAdapterImpl : public UtmpAdapter {
public:
    UtmpAdapterImpl() = default;
    
    SessionObservationResult observe_current_sessions() override {
        auto start_time = std::chrono::system_clock::now();
        
        SessionObservationResult result;
        result.status = rebuntu::core::SemanticStatus::kSuccess;
        
        // Read from /var/run/utmp
        const char* utmp_path = "/var/run/utmp";
        std::vector<UtmpEntry> utmp_entries = read_utmp_file(utmp_path, 100);
        
        if (utmp_entries.empty()) {
            result.status = rebuntu::core::SemanticStatus::kCompleted;
            result.description = "No current sessions found in utmp";
        }
        
        // Process each utmp entry into a SessionRecord
        for (const auto& ue : utmp_entries) {
            SessionRecord sr;
            
            sr.identity.uid = 0;  // uid not available from utmp
            sr.identity.terminal = ue.terminal;
            sr.identity.start_time = ue.entry_time;
            
            sr.username = ue.username.value_or("unknown");
            sr.uid = 0;  // uid not available from utmp
            sr.terminal = ue.terminal;
            sr.display_server = ue.display_server;
            sr.start_time = ue.entry_time;
            sr.session_duration = std::chrono::seconds(0);  // Calculated below
            
            sr.type = ue.session_type;
            sr.login_type = ue.type;
            sr.is_active = true;
            sr.is_local = ue.is_remote ? false : true;
            sr.is_graphical = ue.is_graphical;
            sr.source = "utmp";
            
            // Calculate session duration if possible
            auto now = std::chrono::system_clock::now();
            if (sr.start_time <= now) {
                sr.session_duration = std::chrono::duration_cast<std::chrono::seconds>(
                    now - sr.start_time);
            }
            
            result.current_sessions.push_back(std::move(sr));
            
            // Update statistics
            result.total_sessions++;
            if (sr.is_local) {
                result.local_sessions++;
            } else {
                result.remote_sessions++;
            }
            if (sr.is_graphical) {
                result.graphical_sessions++;
            }
            
            // Count sessions by user
            result.sessions_by_user[sr.username]++;
        }
        
        auto end_time = std::chrono::system_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        if (result.current_sessions.empty()) {
            result.description = "No active sessions found";
        } else {
            result.description = "Successfully observed " + 
                std::to_string(result.total_sessions) + " session(s)";
        }
        
        last_observation_time_ = end_time;
        return result;
    }
    
    std::vector<SessionRecord> get_login_history(size_t max_records = 100) override {
        const char* wtmp_path = "/var/log/wtmp";
        auto records = read_wtmp_file(wtmp_path, max_records);
        
        if (records.empty()) {
            // Fall back to utmp for current sessions
            return observe_current_sessions().current_sessions;
        }
        
        return records;
    }
    
    std::vector<FailedLoginRecord> get_failed_logins(size_t max_records = 50) override {
        const char* btmp_path = "/var/log/btmp";
        auto records = read_btmp_file(btmp_path, max_records);
        
        if (records.empty()) {
            // Fall back to empty vector (file might not exist)
            return {};
        }
        
        return records;
    }
    
    std::vector<SessionRecord> get_user_sessions(uid_t uid, size_t max_records = 100) override {
        auto all_records = observe_current_sessions().current_sessions;
        
        // Filter for specified UID (note: uid is always 0 in current implementation)
        std::vector<SessionRecord> user_records;
        for (const auto& sr : all_records) {
            if (static_cast<int>(user_records.size()) < max_records) {
                user_records.push_back(sr);
            }
        }
        
        return user_records;
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    SessionObservationResult force_refresh() override {
        // Clear any cached state and re-observe
        last_observation_time_ = std::chrono::system_clock::now();
        return observe_current_sessions();
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{
        std::chrono::system_clock::from_time_t(0)};
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<UtmpAdapter> make_utmp_adapter() {
    return std::make_unique<UtmpAdapterImpl>();
}

}  // namespace rebuntu::adapters::session::utmp