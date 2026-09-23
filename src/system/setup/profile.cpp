// rebuntu::setup::profile — Initial Profile Generation & Application (Phase 1.10)
//
// This implements Rebuntu's canonical interface for generating and applying
// initial profiles: bounded bootstrap representations of configuration
// derived from explicit user input, preferences, and discovered host facts.

#include <system/setup/profile.hpp>

#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

namespace fs = std::filesystem;

namespace rebuntu::setup::profile {

// ============================================================================
// Helper Functions
// ============================================================================

namespace {

// Detect effective scope based on current context (same as setup.cpp)
GenerationContext detect_context(const GenerationContext& ctx) {
    GenerationContext result = ctx;
    
    // Determine root path (system vs user)
    uid_t uid = geteuid();
    if (ctx.scope == GenerationContext::Scope::kSystem || uid == 0) {
        result.root_path = "/";
        result.config_dir = "/etc/rebuntu";
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            result.root_path = std::string(home);
            result.config_dir = std::string(home) + "/.config/rebuntu";
        } else {
            result.root_path = "/";
            result.config_dir = "/etc/rebuntu";
        }
    }
    
    return result;
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
    defaults["core.phase"] = "1.10";
    defaults["profile.initialized"] = "true";
    
    return defaults;
}

// Determine derivation reason based on source and context
DerivationReason determine_derivation_reason(
    const std::string& key,
    ProfileSource source,
    const GenerationContext& ctx) {
    
    // Check if policy-enforced
    if (ctx.policy_enforced.count(key) > 0) {
        return DerivationReason::kPolicyEnforced;
    }
    
    switch (source) {
        case ProfileSource::kUserInput:
            return DerivationReason::kUserChoice;
        case ProfileSource::kPreference:
            // Check if it's a preference-based selection from discovery
            if (!ctx.available_options.empty()) {
                return DerivationReason::kPreferenceSatisfied;
            }
            return DerivationReason::kDefaultFallback;
        case ProfileSource::kDefault:
            return DerivationReason::kDefaultFallback;
        case ProfileSource::kDiscovery:
            return DerivationReason::kDiscoveryBased;
        case ProfileSource::kPolicy:
            return DerivationReason::kPolicyEnforced;
    }
    
    return DerivationReason::kDefaultFallback;
}

// Get available options for a key (from discovery)
std::vector<std::string> get_available_options(
    const std::string& key,
    const GenerationContext& ctx) {
    
    auto it = ctx.available_options.find(key);
    if (it != ctx.available_options.end()) {
        return it->second;
    }
    return {};
}

}  // namespace

// ============================================================================
// API Implementation
// ============================================================================

Profile generate_profile(const GenerationContext& ctx) {
    Profile profile;
    profile.status = ProfileStatus::kGenerating;
    
    auto actual_ctx = detect_context(ctx);
    
    // Track derivation reasons for each value
    std::map<std::string, DerivationReason> derivation_reasons;
    
    // Step 1: Policy-enforced values (highest priority)
    for (const auto& key : ctx.policy_enforced) {
        ProfileValue pv;
        pv.key = key;
        // For now, use a placeholder - real policy enforcement would have specific values
        pv.value = "policy_enforced";
        pv.source = ProfileSource::kPolicy;
        pv.reason = DerivationReason::kPolicyEnforced;
        
        profile.values[key] = std::move(pv);
    }
    
    // Step 2: User inputs/choices (explicit selections)
    for (const auto& [key, value] : ctx.user_inputs) {
        ProfileValue pv;
        pv.key = key;
        pv.value = value;
        pv.source = ProfileSource::kUserInput;
        pv.reason = determine_derivation_reason(key, ProfileSource::kUserInput, actual_ctx);
        
        profile.values[key] = std::move(pv);
    }
    
    // Step 3: Preference satisfaction (from available options)
    for (const auto& [key, ctx_values] : ctx.available_options) {
        if (profile.values.find(key) != profile.values.end()) {
            continue;  // Already set by user input or policy
        }
        
        if (!ctx_values.empty()) {
            ProfileValue pv;
            pv.key = key;
            pv.value = ctx_values[0];  // Use first available option
            pv.source = ProfileSource::kPreference;
            pv.reason = determine_derivation_reason(key, ProfileSource::kPreference, actual_ctx);
            pv.discovery_fact_name = "discovered_" + key;
            
            profile.values[key] = std::move(pv);
        }
    }
    
    // Step 4: Discovery-based defaults (based on host capabilities)
    // These would use the environment::discovery results
    
    // Step 5: Built-in defaults (fallbacks)
    auto defaults = get_default_config();
    for (const auto& [key, value] : defaults) {
        if (profile.values.find(key) == profile.values.end()) {
            ProfileValue pv;
            pv.key = key;
            pv.value = value;
            pv.source = ProfileSource::kDefault;
            pv.reason = DerivationReason::kDefaultFallback;
            
            profile.values[key] = std::move(pv);
        }
    }
    
    // Collect derived values for audit
    for (const auto& [key, pv] : profile.values) {
        if (!ctx.user_inputs.count(key)) {
            profile.derived_values.push_back(pv);
        }
    }
    
    // Sort derived values by key for deterministic ordering
    std::sort(profile.derived_values.begin(), profile.derived_values.end(),
              [](const ProfileValue& a, const ProfileValue& b) { return a.key < b.key; });
    
    profile.status = ProfileStatus::kGenerated;
    return profile;
}

core::Outcome validate_profile(const Profile& profile) {
    // Validate required keys
    for (const auto& [key, pv] : profile.values) {
        if (pv.value.empty()) {
            return core::Outcome::failure(
                "E_PROFILE_VALIDATION_ERROR",
                "Profile value '" + key + "' has empty value");
        }
    }
    
    // Check for duplicates
    std::set<std::string> seen_keys;
    for (const auto& [key, _] : profile.values) {
        if (!seen_keys.insert(key).second) {
            return core::Outcome::failure(
                "E_PROFILE_DUPLICATE_KEY",
                "Duplicate key in profile: " + key);
        }
    }
    
    return core::Outcome::success();
}

ProfileDiff diff_profile(
    const std::map<std::string, std::string>& current_config,
    const Profile& target_profile) {
    
    ProfileDiff diff;
    
    // Find added and modified values
    for (const auto& [key, pv] : target_profile.values) {
        auto it = current_config.find(key);
        if (it == current_config.end()) {
            diff.added.push_back({key, pv.value});
        } else if (it->second != pv.value) {
            diff.modified.push_back({key, {it->second, pv.value}});
        }
    }
    
    // Find removed values
    for (const auto& [key, _] : current_config) {
        if (target_profile.values.find(key) == target_profile.values.end()) {
            diff.removed.push_back(key);
        }
    }
    
    return diff;
}

ProfilePlan plan_profile_application(const Profile& profile, const GenerationContext& ctx) {
    ProfilePlan plan;
    
    // If no changes needed
    if (profile.values.empty()) {
        plan.is_no_op = true;
        plan.steps.push_back("No changes required - profile already matches");
        return plan;
    }
    
    // Generate steps
    for (const auto& [key, pv] : profile.values) {
        std::ostringstream ss;
        ss << "Set " << key << " = " << pv.value;
        ss << " [" << to_string(pv.source);
        
        if (!pv.discovery_fact_name.has_value()) {
            ss << "]";
        } else {
            ss << ", fact=" << pv.discovery_fact_name.value() << "]";
        }
        
        plan.steps.push_back(ss.str());
    }
    
    // Add verification step
    plan.steps.push_back("Verify profile application");
    
    return plan;
}

SetupResult apply_profile(const Profile& profile, const GenerationContext& ctx) {
    SetupResult result;
    
    auto actual_ctx = detect_context(ctx);
    result.phase = SetupPhase::kInProgress;
    
    // Step 1: Validate
    auto validation_result = validate_profile(profile);
    if (!validation_result.is_success()) {
        result.phase = SetupPhase::kFailed;
        if (validation_result.error.has_value()) {
            result.error_code = validation_result.error->code;
            result.error_message = validation_result.error->message;
        }
        return result;
    }
    
    // Step 2: Plan
    auto plan = plan_profile_application(profile, ctx);
    
    // If no-op, skip to verification
    if (plan.is_no_op) {
        result.success = true;
        result.verified = true;
        result.phase = SetupPhase::kComplete;
        result.is_no_op = true;
        return result;
    }
    
    // Step 3: Checkpoint/Backup (if not dry_run)
    std::string config_path = actual_ctx.config_dir + "/config";
    
    if (!ctx.dry_run && path_exists(config_path)) {
        // In a real implementation, we would create a backup
        // For now, just note it in the plan
    }
    
    // Step 4: Execute - write configuration file
    std::ostringstream config_content;
    for (const auto& [key, pv] : profile.values) {
        config_content << key << "=" << pv.value << "\n";
    }
    
    if (!ctx.dry_run) {
        // Ensure directory exists
        if (!path_exists(actual_ctx.config_dir)) {
            if (!create_directory(actual_ctx.config_dir)) {
                result.phase = SetupPhase::kFailed;
                result.error_code = kErrorSetupArtifactMissing;
                result.error_message = "Failed to create configuration directory: " + actual_ctx.config_dir;
                return result;
            }
        }
        
        // Write config file
        if (!write_config_file_atomic(config_path, config_content.str())) {
            result.phase = SetupPhase::kFailed;
            result.error_code = kErrorConfigParseError;
            result.error_message = "Failed to write configuration file: " + config_path;
            return result;
        }
    }
    
    // Step 5: Verify
    if (!ctx.dry_run) {
        auto readback_opt = read_config_file(config_path);
        
        if (!readback_opt.has_value() || readback_opt->empty()) {
            result.phase = SetupPhase::kDegraded;
            result.error_code = kErrorVerificationFailed;
            result.error_message = "Configuration file written but could not be verified";
            return result;
        }
        
        auto parsed = parse_config_content(readback_opt.value());
        
        // Verify all values are present
        bool verified = true;
        for (const auto& [key, pv] : profile.values) {
            if (parsed.find(key) == parsed.end() || parsed[key] != pv.value) {
                verified = false;
                break;
            }
        }
        
        result.verified = verified;
        result.success = verified;
        result.phase = verified ? SetupPhase::kComplete : SetupPhase::kFailed;
    } else {
        // Dry run
        result.success = true;
        result.verified = false;
        result.phase = SetupPhase::kComplete;
    }
    
    // Step 6: Record evidence
    for (const auto& [key, pv] : profile.values) {
        ConfigurationValue cv;
        cv.key = key;
        cv.value = pv.value;
        cv.source = ConfigurationSource::kUserConfig;  // Profile values are user config
        cv.is_default = false;
        
        result.configurations.push_back(cv);
    }
    
    return result;
}

Profile load_profile(const std::string& config_dir) {
    Profile profile;
    
    std::string config_path = config_dir + "/config";
    
    if (!path_exists(config_path)) {
        // No existing profile - return empty with defaults
        profile.status = ProfileStatus::kPending;
        
        auto defaults = get_default_config();
        for (const auto& [key, value] : defaults) {
            ProfileValue pv;
            pv.key = key;
            pv.value = value;
            pv.source = ProfileSource::kDefault;
            pv.reason = DerivationReason::kDefaultFallback;
            
            profile.values[key] = std::move(pv);
        }
        
        return profile;
    }
    
    auto content_opt = read_config_file(config_path);
    
    if (!content_opt.has_value()) {
        profile.status = ProfileStatus::kFailed;
        profile.error_message = "Failed to read configuration file";
        return profile;
    }
    
    auto parsed = parse_config_content(content_opt.value());
    
    for (const auto& [key, value] : parsed) {
        ProfileValue pv;
        pv.key = key;
        pv.value = value;
        pv.source = ProfileSource::kUserInput;  // Loaded from storage
        pv.reason = DerivationReason::kUserChoice;
        
        profile.values[key] = std::move(pv);
    }
    
    profile.status = ProfileStatus::kApplied;
    
    return profile;
}

SetupResult reapply_profile(
    const Profile& original_profile,
    const std::map<std::string, std::string>& current_config,
    const GenerationContext& ctx) {
    
    SetupResult result;
    
    auto actual_ctx = detect_context(ctx);
    result.phase = SetupPhase::kInProgress;
    
    // Calculate diff
    auto diff = diff_profile(current_config, original_profile);
    
    if (diff.is_empty()) {
        // Already matches - no-op
        result.success = true;
        result.verified = true;
        result.phase = SetupPhase::kComplete;
        result.is_no_op = true;
        return result;
    }
    
    // Generate new profile with current context
    GenerationContext new_ctx = ctx;
    for (const auto& [key, value] : current_config) {
        if (original_profile.values.find(key) == original_profile.values.end()) {
            // Keep user-modified values
            new_ctx.user_inputs[key] = value;
        }
    }
    
    // Reapply
    return apply_profile(original_profile, new_ctx);
}

}  // namespace rebuntu::setup::profile