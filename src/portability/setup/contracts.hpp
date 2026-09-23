#include <cstdint>
// rebuntu::setup — Setup & Configuration Contracts (Phase 1.8)
//
// This establishes Rebuntu's canonical grammar for setup and configuration:
//   * Setup = installation/environment specification ("WHERE")
//   * Configuration = variable specification evaluated at init ("WITH WHAT")
//
// Core principles:
//   * Setup ≠ Installation
//       - Setup = initial environment state after install
//       - Installation = artifact placement/establishment
//   * Setup ≠ Configuration
//       - Setup = relatively non-variable environment specification
//       - Configuration = variable parameters applied at initialization
//   * Configuration ≠ State
//       - Configuration = desired/desired state (specification)
//       - State = authoritative runtime-owned data

#pragma once

#include <runtime/core/contracts.hpp>
#include <algorithm>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::setup {

// SetupPhase: The distinct phases of setup lifecycle
enum class SetupPhase {
    kNotStarted,     // No setup attempted yet
    kInProgress,     // Setup is currently running
    kComplete,       // Setup completed successfully
    kFailed,         // Setup failed
    kDegraded,       // Setup completed but with warnings
};

inline std::string_view to_string(SetupPhase p) {
    switch (p) {
        case SetupPhase::kNotStarted: return "not_started";
        case SetupPhase::kInProgress: return "in_progress";
        case SetupPhase::kComplete:   return "complete";
        case SetupPhase::kFailed:     return "failed";
        case SetupPhase::kDegraded:   return "degraded";
    }
    return "unknown";
}

// ConfigurationSource: Where configuration originates
enum class ConfigurationSource {
    kDefault,        // Built-in defaults (deterministic)
    kSystemConfig,   // System-wide (/etc/rebuntu)
    kUserConfig,     // User-level (~/.config/rebuntu)
    kEnvironment,    // Environment variables
    kOverride,       // Invocation-time override
};

inline std::string_view to_string(ConfigurationSource s) {
    switch (s) {
        case ConfigurationSource::kDefault:   return "default";
        case ConfigurationSource::kSystemConfig: return "system_config";
        case ConfigurationSource::kUserConfig: return "user_config";
        case ConfigurationSource::kEnvironment: return "environment";
        case ConfigurationSource::kOverride:  return "override";
    }
    return "unknown";
}

// ConfigurationMode: How configuration is applied
enum class ConfigurationMode {
    kStandard,   // Normal operation with full validation
    kStrict,     // Strict mode - reject unknown/invalid values
    kPermissive, // Permissive mode - accept and log but warn
};

inline std::string_view to_string(ConfigurationMode m) {
    switch (m) {
        case ConfigurationMode::kStandard:   return "standard";
        case ConfigurationMode::kStrict:     return "strict";
        case ConfigurationMode::kPermissive: return "permissive";
    }
    return "unknown";
}

// SetupArtifact: A managed setup artifact
struct SetupArtifact {
    std::string name;           // Logical name (e.g., "config_directory")
    std::string path;           // Physical path
    bool is_required = true;    // Must exist for successful setup
    
    enum class State {
        kMissing,
        kCreated,
        kVerified,
        kUpdated,
    } state = State::kMissing;
    
    std::optional<std::string> owner;
    std::optional<uint32_t> mode;
};

// ConfigurationValue: A configuration entry with provenance
struct ConfigurationValue {
    std::string key;            // Configuration key
    std::string value;          // Configuration value
    
    ConfigurationSource source = ConfigurationSource::kDefault;
    bool is_default = false;
    
    // Validation status
    enum class ValidationResult {
        kUnknown,
        kValid,
        kInvalid,
        kWarning,
    } validation_status = ValidationResult::kUnknown;
    
    std::optional<std::string> error_message;
};

// SetupResult: Result of a setup operation
struct SetupResult {
    SetupPhase phase = SetupPhase::kNotStarted;
    
    bool success = false;
    bool verified = false;  // Postconditions independently verified
    
    std::vector<SetupArtifact> artifacts;
    
    // Configuration applied
    std::vector<ConfigurationValue> configurations;
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
    
    // Idempotency: whether this was a no-op (already in desired state)
    bool is_no_op = false;
};

// ConfigurationResult: Result of loading/applying configuration
struct ConfigurationResult {
    bool success = false;
    
    std::vector<ConfigurationValue> values;
    
    // Source precedence (highest to lowest priority)
    std::vector<ConfigurationSource> active_sources;
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
};

// SetupContext: Context for setup operations
struct SetupContext {
    // Scope
    enum class Scope {
        kSystem,   // System-wide setup
        kUser,     // Per-user setup
        kSession,  // Per-session (transient)
    } scope = Scope::kSystem;
    
    // Target paths
    std::string root_path;      // Root for relative paths
    std::string config_dir;     // Configuration directory
    std::string state_dir;      // State directory
    
    // Mode
    ConfigurationMode mode = ConfigurationMode::kStandard;
    
    // Flags
    bool dry_run = false;       // Don't actually mutate
    bool skip_verification = false;
    bool force_reconfigure = false;  // Reapply even if appears configured
};

// SetupIntent: User's desired setup state
struct SetupIntent {
    std::optional<std::string> version;      // Target version
    
    // Initial configuration
    std::map<std::string, std::string> initial_config;
    
    // Features to enable/disable
    std::set<std::string> enabled_features;
    std::set<std::string> disabled_features;
};

// ConfigurationErrorCodes (Phase 1.8)
inline constexpr std::string_view kErrorConfigNotFound = "E_CONFIG_NOT_FOUND";
inline constexpr std::string_view kErrorConfigParseError = "E_CONFIG_PARSE_ERROR";
inline constexpr std::string_view kErrorConfigValidationError = "E_CONFIG_VALIDATION_ERROR";
inline constexpr std::string_view kErrorSetupArtifactMissing = "E_SETUP_ARTIFACT_MISSING";
inline constexpr std::string_view kErrorVerificationFailed = "E_VERIFICATION_FAILED";

// ============================================================================
// Setup API (Phase 1.8)
// ============================================================================

// Build a default setup context based on current host state
SetupContext build_default_context();

// Apply configuration from multiple sources with precedence
ConfigurationResult apply_configuration(
    const std::map<std::string, std::string>& user_config,
    ConfigurationMode mode = ConfigurationMode::kStandard);

// Perform initial environment setup (create directories, write config)
SetupResult setup_initial_environment(const SetupIntent& intent, const SetupContext& ctx_override);

// Reconfigure existing environment with new settings
SetupResult setup_reconfigure(const SetupContext& context, const std::map<std::string, std::string>& config);

// Load configuration from a directory
ConfigurationResult load_configuration(const std::string& config_dir);

}  // namespace rebuntu::setup
