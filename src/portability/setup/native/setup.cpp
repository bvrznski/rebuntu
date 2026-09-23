// rebuntu::setup — Setup & Configuration Machinery (Phase 1.8)
//
// This implements the canonical interface for Rebuntu setup and configuration:
//   * Setup = initial environment state after installation
//   * Configuration = variable parameters applied at initialization

#include <portability/setup/contracts.hpp>

#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace rebuntu::setup {
namespace {

// Detect effective scope based on current context
SetupContext detect_context() {
    SetupContext ctx;
    
    // Determine root path (system vs user)
    uid_t uid = geteuid();
    ctx.scope = (uid == 0) ? SetupContext::Scope::kSystem : SetupContext::Scope::kUser;
    
    const char* home = std::getenv("HOME");
    if (home) {
        ctx.root_path = (ctx.scope == SetupContext::Scope::kSystem) ? "/" : std::string(home);
    } else {
        ctx.root_path = "/";
    }
    
    // Set up paths
    if (ctx.scope == SetupContext::Scope::kSystem) {
        ctx.config_dir = "/etc/rebuntu";
        ctx.state_dir = "/var/lib/rebuntu";
    } else {
        ctx.config_dir = ctx.root_path + "/.config/rebuntu";
        ctx.state_dir = ctx.root_path + "/.local/state/rebuntu";
    }
    
    return ctx;
}

// Check if a path exists
bool path_exists(const std::string& path) {
    std::error_code ec;
    return fs::exists(fs::path(path), ec);
}

// Create directory with appropriate permissions
bool create_directory(const std::string& path, uint32_t mode = 0755) {
    std::error_code ec;
    
    // Check if already exists and is a directory
    if (fs::is_directory(fs::path(path), ec)) {
        return true;
    }
    
    // Create with parent directories
    fs::create_directories(fs::path(path), ec);
    if (ec) {
        return false;
    }
    
    // Set permissions if specified
    fs::permissions(fs::path(path), static_cast<fs::perms>(mode), ec);
    return !ec;
}

// Write configuration file atomically using temp file + rename
bool write_config_file_atomic(const std::string& path, const std::string& content) {
    std::error_code ec;
    
    // Create temp file in same directory for atomic rename
    fs::path dir = fs::path(path).parent_path();
    if (!dir.empty() && !fs::exists(dir, ec)) {
        create_directory(dir.string());
    }
    
    fs::path temp_path = dir / fs::path(path).filename();
    temp_path += ".tmp.";
    temp_path += std::to_string(getpid());
    
    // Write to temp file
    {
        std::ofstream ofs(temp_path, std::ios::out | std::ios::trunc);
        if (!ofs) return false;
        ofs << content;
        if (ofs.fail()) return false;
    }
    
    // Make temp file readable/writable by owner only
    fs::permissions(temp_path, fs::perms::owner_all, ec);
    if (ec) {
        fs::remove(temp_path, ec);
        return false;
    }
    
    // Atomic rename
    fs::rename(temp_path, fs::path(path), ec);
    return !ec;
}

// Read configuration file content
std::optional<std::string> read_config_file(const std::string& path) {
    std::error_code ec;
    
    if (!fs::is_regular_file(fs::path(path), ec)) {
        return std::nullopt;
    }
    
    std::ifstream ifs(path, std::ios::in);
    if (!ifs) {
        return std::nullopt;
    }
    
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

// Parse simple key=value config format
std::map<std::string, std::string> parse_config_content(const std::string& content) {
    std::map<std::string, std::string> result;
    
    std::istringstream stream(content);
    std::string line;
    
    while (std::getline(stream, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        
        // Find '=' separator
        size_t eq_pos = line.find('=');
        if (eq_pos != std::string::npos) {
            std::string key = line.substr(0, eq_pos);
            std::string value = line.substr(eq_pos + 1);
            
            // Trim whitespace
            while (!key.empty() && isspace(key.back())) key.pop_back();
            while (!value.empty() && isspace(value.front())) value.erase(0, 1);
            
            if (!key.empty()) {
                result[key] = value;
            }
        }
    }
    
    return result;
}

// Get default configuration values
std::map<std::string, std::string> get_default_config() {
    std::map<std::string, std::string> defaults;
    
    // Core configuration defaults
    defaults["core.version"] = "1.0.0";
    defaults["core.phase"] = "1.8";
    
    // Environment defaults (auto-detected)
    uid_t uid = geteuid();
    defaults["environment.scope"] = (uid == 0) ? "system" : "user";
    
    const char* home = std::getenv("HOME");
    if (home) {
        defaults["environment.home_dir"] = home;
    }
    
    // Feature defaults
    defaults["features.logging.enabled"] = "true";
    defaults["features.logging.level"] = "info";
    
    return defaults;
}

}  // namespace

// ============================================================================
// Setup API Implementation (Phase 1.8)
// ============================================================================

SetupContext build_default_context() {
    return detect_context();
}

ConfigurationResult apply_configuration(
    const std::map<std::string, std::string>& user_config,
    ConfigurationMode mode) {
    
    ConfigurationResult result;
    
    // Get default values first (lowest precedence)
    auto defaults = get_default_config();
    
    // Apply sources in precedence order:
    // User config > Environment > Defaults
    
    // Track active sources
    std::vector<ConfigurationSource> active_sources;
    
    // Process user config (highest precedence among explicit sources)
    for (const auto& [key, value] : user_config) {
        ConfigurationValue cv;
        cv.key = key;
        cv.value = value;
        cv.source = ConfigurationSource::kUserConfig;
        cv.is_default = false;
        cv.validation_status = ConfigurationValue::ValidationResult::kValid;
        
        // In permissive mode, mark unknown fields as warnings
        if (mode == ConfigurationMode::kPermissive && defaults.find(key) == defaults.end()) {
            cv.validation_status = ConfigurationValue::ValidationResult::kWarning;
        }
        
        result.values.push_back(cv);
    }
    
    active_sources.push_back(ConfigurationSource::kUserConfig);
    
    // Add defaults for any missing fields
    for (const auto& [key, default_value] : defaults) {
        bool found = false;
        for (auto& cv : result.values) {
            if (cv.key == key) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            ConfigurationValue cv;
            cv.key = key;
            cv.value = default_value;
            cv.source = ConfigurationSource::kDefault;
            cv.is_default = true;
            
            result.values.push_back(cv);
        }
    }
    
    active_sources.push_back(ConfigurationSource::kDefault);
    
    // Reverse active sources to show highest precedence first
    std::reverse(active_sources.begin(), active_sources.end());
    result.active_sources = active_sources;
    
    result.success = true;
    return result;
}

SetupResult setup_initial_environment(const SetupIntent& intent, const SetupContext& ctx_override) {
    SetupResult result;
    
    // Start with default context
    auto ctx = detect_context();
    
    // Apply scope override if specified
    const char* home = std::getenv("HOME");
    
    switch (ctx_override.scope) {
        case SetupContext::Scope::kUser:
            if (home) {
                ctx.config_dir = std::string(home) + "/.config/rebuntu";
                ctx.state_dir = std::string(home) + "/.local/state/rebuntu";
            }
            break;
        case SetupContext::Scope::kSession:
            // Session-scoped setup uses temporary directories
            ctx.config_dir = "/tmp/rebuntu_session_" + std::to_string(getpid());
            ctx.state_dir = "/tmp/rebuntu_session_" + std::to_string(getpid());
            break;
        default:
            // kSystem or unknown - keep default context
            break;
    }
    
    result.phase = SetupPhase::kInProgress;
    
    // Track artifacts and their states
    struct ArtifactInfo {
        std::string name;
        std::string path;
        bool is_required;
        SetupArtifact::State state;
    };
    
    std::vector<ArtifactInfo> required_artifacts = {
        {"config_directory", ctx.config_dir, true, SetupArtifact::State::kMissing},
        {"state_directory", ctx.state_dir, true, SetupArtifact::State::kMissing}
    };
    
    // Create directories
    for (auto& artifact : required_artifacts) {
        if (path_exists(artifact.path)) {
            artifact.state = SetupArtifact::State::kVerified;
            
            // Verify it's actually a directory
            std::error_code ec;
            if (!fs::is_directory(fs::path(artifact.path), ec)) {
                artifact.state = SetupArtifact::State::kMissing;
                result.phase = SetupPhase::kFailed;
                result.error_code = kErrorSetupArtifactMissing;
                result.error_message = "Path exists but is not a directory: " + artifact.path;
                return result;
            }
        } else {
            if (!ctx_override.dry_run) {
                if (create_directory(artifact.path)) {
                    artifact.state = SetupArtifact::State::kCreated;
                } else {
                    if (artifact.is_required) {
                        artifact.state = SetupArtifact::State::kMissing;
                        result.phase = SetupPhase::kFailed;
                        result.error_code = kErrorSetupArtifactMissing;
                        result.error_message = "Failed to create directory: " + artifact.path;
                        return result;
                    }
                }
            } else {
                // Dry run: assume creation would succeed
                artifact.state = SetupArtifact::State::kCreated;
            }
        }
        
        // Add to result artifacts
        SetupArtifact sa;
        sa.name = artifact.name;
        sa.path = artifact.path;
        sa.is_required = artifact.is_required;
        sa.state = artifact.state;
        result.artifacts.push_back(sa);
    }
    
    // Apply configuration from intent
    auto config_result = apply_configuration(intent.initial_config, ctx_override.mode);
    
    if (!config_result.success) {
        result.phase = SetupPhase::kFailed;
        if (config_result.error_code.has_value()) {
            result.error_code = config_result.error_code;
        } else {
            result.error_code = kErrorConfigValidationError;
        }
        return result;
    }
    
    result.configurations = std::move(config_result.values);
    
    // Write configuration file if not dry run
    if (!ctx_override.dry_run) {
        std::string config_path = ctx.config_dir + "/config";
        
        // Build config content from values
        std::ostringstream ss;
        for (const auto& cv : result.configurations) {
            ss << cv.key << "=" << cv.value << "\n";
        }
        
        if (!write_config_file_atomic(config_path, ss.str())) {
            result.phase = SetupPhase::kDegraded;
            result.error_code = kErrorConfigParseError;
            result.error_message = "Failed to write configuration file (but directories created)";
        }
    } else {
        // Dry run: mark success but don't persist
    }
    
    // Verify final state
    if (!ctx_override.dry_run) {
        bool config_ok = path_exists(ctx.config_dir);
        bool state_ok = path_exists(ctx.state_dir);
        
        result.verified = config_ok && state_ok;
        result.success = result.verified;
        result.phase = result.success ? SetupPhase::kComplete : SetupPhase::kFailed;
    } else {
        // Dry run always succeeds (just simulates)
        result.success = true;
        result.verified = false;  // No postconditions were actually verified
        result.phase = SetupPhase::kComplete;
    }
    
    return result;
}

SetupResult setup_reconfigure(const SetupContext& context, const std::map<std::string, std::string>& config) {
    SetupResult result;
    
    // In strict mode, verify that directories exist
    if (!path_exists(context.config_dir)) {
        result.phase = SetupPhase::kFailed;
        result.error_code = kErrorSetupArtifactMissing;
        result.error_message = "Config directory does not exist: " + context.config_dir;
        return result;
    }
    
    // Apply new configuration
    auto config_result = apply_configuration(config, context.mode);
    
    if (!config_result.success) {
        result.phase = SetupPhase::kFailed;
        if (config_result.error_code.has_value()) {
            result.error_code = config_result.error_code;
        } else {
            result.error_code = kErrorConfigValidationError;
        }
        return result;
    }
    
    // In dry run mode, just validate without writing
    if (context.dry_run) {
        result.success = true;
        result.phase = SetupPhase::kComplete;
        result.configurations = std::move(config_result.values);
        return result;
    }
    
    // Write configuration file
    std::string config_path = context.config_dir + "/config";
    
    std::ostringstream ss;
    for (const auto& cv : config_result.values) {
        ss << cv.key << "=" << cv.value << "\n";
    }
    
    if (!write_config_file_atomic(config_path, ss.str())) {
        result.phase = SetupPhase::kFailed;
        result.error_code = kErrorConfigParseError;
        result.error_message = "Failed to write configuration file: " + config_path;
        return result;
    }
    
    // Verify
    std::optional<std::string> readback = read_config_file(config_path);
    
    if (!readback.has_value() || readback.value().empty()) {
        result.phase = SetupPhase::kDegraded;
        result.error_code = kErrorVerificationFailed;
        result.error_message = "Configuration file written but could not be verified";
        return result;
    }
    
    // Parse and verify content matches
    auto parsed = parse_config_content(readback.value());
    bool verified = (parsed.size() == config_result.values.size());
    
    for (const auto& [key, value] : config) {
        if (parsed.find(key) == parsed.end() || parsed[key] != value) {
            verified = false;
            break;
        }
    }
    
    result.verified = verified;
    result.success = verified;
    result.phase = verified ? SetupPhase::kComplete : SetupPhase::kDegraded;
    result.configurations = std::move(config_result.values);
    
    return result;
}

ConfigurationResult load_configuration(const std::string& config_dir) {
    ConfigurationResult result;
    
    std::string config_path = config_dir + "/config";
    
    if (!path_exists(config_path)) {
        // No existing configuration - use defaults
        auto defaults = get_default_config();
        
        for (const auto& [key, value] : defaults) {
            ConfigurationValue cv;
            cv.key = key;
            cv.value = value;
            cv.source = ConfigurationSource::kDefault;
            cv.is_default = true;
            cv.validation_status = ConfigurationValue::ValidationResult::kValid;
            
            result.values.push_back(cv);
        }
        
        result.active_sources = {ConfigurationSource::kDefault};
        result.success = true;
        return result;
    }
    
    auto content_opt = read_config_file(config_path);
    
    if (!content_opt.has_value()) {
        result.error_code = kErrorConfigNotFound;
        result.error_message = "Configuration file exists but could not be read: " + config_path;
        return result;
    }
    
    auto parsed = parse_config_content(content_opt.value());
    
    for (const auto& [key, value] : parsed) {
        ConfigurationValue cv;
        cv.key = key;
        cv.value = value;
        cv.source = ConfigurationSource::kUserConfig;  // User-provided config
        cv.is_default = false;
        cv.validation_status = ConfigurationValue::ValidationResult::kValid;
        
        result.values.push_back(cv);
    }
    
    result.active_sources = {ConfigurationSource::kUserConfig, ConfigurationSource::kDefault};
    result.success = true;
    
    return result;
}

}  // namespace rebuntu::setup