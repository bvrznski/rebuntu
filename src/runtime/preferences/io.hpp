// rebuntu::runtime::preferences::io — Preferences File I/O (Phase 1.7)
//
// This provides file-based persistence for preferences using native Linux
// configuration mechanisms: XDG Base Directory, environment.d, systemd credentials.
//
// Core principles:
//   * XDG_CONFIG_HOME/Rebuntu/preferences.toml - User preferences
//   * XDG_CONFIG_DIRS/Rebuntu/preferences.toml - System preferences
//   * /etc/environment.d/*.conf - Environment-based preference overrides

#pragma once

#include <runtime/preferences.hpp>
#include <string>
#include <map>
#include <optional>
#include <filesystem>

namespace rebuntu::runtime::preferences {

// PreferenceFileSource: Origin of a preference value from file
enum class PreferenceFileSource {
    kSystemConfig,      // /etc/Rebuntu or XDG_CONFIG_DIRS
    kUserConfig,        // ~/.config/Rebuntu or XDG_CONFIG_HOME
    kEnvironmentD,      // /etc/environment.d/*.conf
    kSessionEnv,        // SESSION_* environment variables
};

inline std::string_view to_string(PreferenceFileSource s) {
    switch (s) {
        case PreferenceFileSource::kSystemConfig: return "system_config";
        case PreferenceFileSource::kUserConfig:   return "user_config";
        case PreferenceFileSource::kEnvironmentD: return "environment_d";
        case PreferenceFileSource::kSessionEnv:   return "session_env";
    }
    return "unknown";
}

// XDG Paths for preference storage
struct PreferencePaths {
    std::filesystem::path user_config_dir;      // $XDG_CONFIG_HOME/Rebuntu or ~/.config/Rebuntu
    std::filesystem::path system_config_dir;    // $XDG_CONFIG_DIRS/Rebuntu or /etc/Rebuntu
    std::filesystem::path env_d_dir;            // /etc/environment.d
    
    PreferencePaths() : env_d_dir("/etc/environment.d") {
        if (const char* xdg_config_home = std::getenv("XDG_CONFIG_HOME")) {
            user_config_dir = std::filesystem::path(xdg_config_home) / "Rebuntu";
        } else if (const char* home = std::getenv("HOME")) {
            user_config_dir = std::filesystem::path(home) / ".config" / "Rebuntu";
        } else {
            user_config_dir = "/etc/Rebuntu";  // Fallback
        }
        
        if (const char* xdg_config_dirs = std::getenv("XDG_CONFIG_DIRS")) {
            system_config_dir = std::filesystem::path(xdg_config_dirs) / "Rebuntu";
        } else {
            system_config_dir = "/etc/Rebuntu";
        }
    }
};

// PreferenceStorage: File-based persistence for preferences
class PreferenceStorage {
public:
    explicit PreferenceStorage(PreferencePaths paths)
        : paths_(std::move(paths)) {}
    
    // Load all preferences from file
    std::map<std::string, PreferenceValue> load_preferences() const;
    
    // Save all preferences to file - returns success/failure status
    bool save_preferences(const std::map<std::string, PreferenceValue>& values) const;
    
    // Load environment.d configuration
    std::vector<PreferenceValue> load_environment_d() const;
    
    // Get preference paths for diagnostics
    const PreferencePaths& paths() const { return paths_; }
    
    // Path to user preferences file
    std::filesystem::path user_prefs_path() const {
        return paths_.user_config_dir / "preferences.toml";
    }
    
    // Path to system preferences file  
    std::filesystem::path system_prefs_path() const {
        return paths_.system_config_dir / "preferences.toml";
    }

private:
    PreferencePaths paths_;
    
    // Parse TOML-style preference file (simple key-value format)
    std::map<std::string, PreferenceValue> parse_preference_file(
        const std::filesystem::path& path) const;
};

// EnvironmentPreferenceResolver: Resolve preferences from environment
class EnvironmentPreferenceResolver {
public:
    // Get all environment-based preference overrides
    static std::map<std::string, PreferenceValue> resolve_from_environment();
    
    // Check if a specific environment variable is set for a preference
    static std::optional<PreferenceValue> get_env_preference(std::string_view pref_id);
};

// SessionPreferences: Session-level preference overrides
class SessionPreferences {
public:
    // Load session preferences (e.g., from systemd user session)
    std::map<std::string, PreferenceValue> load() const;
    
    // Set a session preference (temporary, not persisted)
    void set(std::string id, std::string value);
    
    // Clear all session preferences
    void clear();
    
    // Get session preference values
    std::map<std::string, PreferenceValue> get_all() const;

private:
    std::map<std::string, PreferenceValue> session_values_;
};

}  // namespace rebuntu::runtime::preferences