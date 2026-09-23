// rebuntu::setup::profile — Initial Profile Generation & Application (Phase 1.10)
//
// This establishes Rebuntu's canonical grammar for generating and applying
// initial profiles: bounded bootstrap representations of configuration
// derived from explicit user input, preferences, and discovered host facts.
//
// Core principles:
//   * Profile ≠ Preference
//       - Profile = derived configuration based on choices + constraints + capabilities
//       - Preference = soft choice that may be unsatisfied
//   * Profile ≠ Configuration
//       - Profile = initial setup state (deterministic derivation)
//       - Configuration = runtime-applied parameters (may vary by instance)
//   * Generation ≠ Application
//       - Generate = produce profile from inputs and discovery
//       - Apply = write profile to configuration storage

#pragma once

#include <runtime/core/contracts.hpp>
#include <portability/setup/contracts.hpp>
#include <algorithm>
#include <string>
#include <string_view>
#include <map>
#include <optional>
#include <set>
#include <vector>

namespace rebuntu::setup::profile {

// ProfileSource: Where profile data originates
enum class ProfileSource {
    kUserInput,       // Explicit user choices
    kPreference,      // User preferences (soft, may be unsatisfied)
    kDefault,         // Built-in deterministic defaults
    kDiscovery,       // Host fact discovery (CPU, memory, GPU, etc.)
    kPolicy,          // Policy-enforced constraints
};

inline std::string_view to_string(ProfileSource s) {
    switch (s) {
        case ProfileSource::kUserInput:   return "user_input";
        case ProfileSource::kPreference:  return "preference";
        case ProfileSource::kDefault:     return "default";
        case ProfileSource::kDiscovery:   return "discovery";
        case ProfileSource::kPolicy:      return "policy";
    }
    return "unknown";
}

// ProfileStatus: Status of profile generation/application
enum class ProfileStatus {
    kPending,         // Not yet generated/applied
    kGenerating,      // Currently generating
    kGenerated,       // Generated but not applied
    kApplying,        // Currently applying
    kApplied,         // Successfully applied
    kFailed,          // Failed during generation or application
    kDegraded,        // Applied with warnings
};

inline std::string_view to_string(ProfileStatus s) {
    switch (s) {
        case ProfileStatus::kPending:     return "pending";
        case ProfileStatus::kGenerating:  return "generating";
        case ProfileStatus::kGenerated:   return "generated";
        case ProfileStatus::kApplying:    return "applying";
        case ProfileStatus::kApplied:     return "applied";
        case ProfileStatus::kFailed:      return "failed";
        case ProfileStatus::kDegraded:    return "degraded";
    }
    return "unknown";
}

// DerivationReason: Why a value was selected in the profile
enum class DerivationReason {
    kUserChoice,          // Explicit user selection
    kPreferenceSatisfied, // Preference satisfied by available option
    kDefaultFallback,     // Default used because no preference/match
    kDiscoveryBased,      // Derived from host discovery facts
    kPolicyEnforced,      // Required by policy constraints
};

inline std::string_view to_string(DerivationReason r) {
    switch (r) {
        case DerivationReason::kUserChoice:       return "user_choice";
        case DerivationReason::kPreferenceSatisfied:return "preference_satisfied";
        case DerivationReason::kDefaultFallback:  return "default_fallback";
        case DerivationReason::kDiscoveryBased:   return "discovery_based";
        case DerivationReason::kPolicyEnforced:   return "policy_enforced";
    }
    return "unknown";
}

// ProfileValue: A value in the profile with derivation metadata
struct ProfileValue {
    std::string key;                      // Configuration key (e.g., "provider.preferred")
    
    std::string value;                    // The derived value
    
    ProfileSource source = ProfileSource::kDefault;
    DerivationReason reason = DerivationReason::kDefaultFallback;
    
    // Provenance: where the data came from
    std::optional<std::string> source_description;  // Human-readable source info
    
    // Discovery fact reference (if discovery-based)
    std::optional<std::string> discovery_fact_name;
};

// Profile: A complete profile with values and metadata
struct Profile {
    std::map<std::string, ProfileValue> values;
    
    // Generation metadata
    ProfileStatus status = ProfileStatus::kPending;
    std::optional<std::string> error_message;
    
    // All inputs used (for audit/diff)
    std::vector<std::string> user_inputs;
    std::vector<ProfileValue> derived_values;
    
    // Verification
    bool verified = false;  // Postconditions independently verified
};

// ProfileDiff: Difference between two profiles
struct ProfileDiff {
    std::vector<std::pair<std::string, std::string>> added;      // key -> new_value
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> modified;
        // key -> (old_value, new_value)
    std::vector<std::string> removed;                            // keys removed
    
    bool is_empty() const {
        return added.empty() && modified.empty() && removed.empty();
    }
};

// ProfileGenerationContext: Context for profile generation
struct GenerationContext {
    // Scope
    enum class Scope {
        kSystem,   // System-wide profile (/etc/rebuntu)
        kUser,     // Per-user profile (~/.config/rebuntu)
        kSession,  // Per-session (temporary)
    } scope = Scope::kSystem;
    
    // Paths
    std::string root_path;      // Root for relative paths
    std::string config_dir;     // Configuration directory
    
    // Mode
    bool dry_run = false;
    
    // Input data
    std::map<std::string, std::string> user_inputs;
    std::map<std::string, std::vector<std::string>> available_options;  // discovery results
    
    // Constraints
    std::set<std::string> required_keys;   // Must be present
    std::set<std::string> policy_enforced; // Cannot be overridden
    
    // Flags
    bool skip_verification = false;
};

// ProfilePlan: Execution plan for applying a profile
struct ProfilePlan {
    std::vector<std::string> steps;
    
    bool is_no_op = false;  // No changes needed (already matches)
    bool requires_reboot = false;
    
    std::optional<std::string> rollback_description;
};

// ============================================================================
// API Functions
// ============================================================================

// Generate a profile from inputs and discovery facts
//
// Derivation logic:
//   1. Policy-enforced values (highest priority, cannot be overridden)
//   2. User inputs/choices (explicit selections)
//   3. Preference satisfaction (from available options)
//   4. Discovery-based defaults (based on host capabilities)
//   5. Built-in defaults (fallbacks)
//
Profile generate_profile(const GenerationContext& ctx);

// Validate a profile against schema constraints
core::Outcome validate_profile(const Profile& profile);

// Calculate difference between current configuration and target profile
ProfileDiff diff_profile(
    const std::map<std::string, std::string>& current_config,
    const Profile& target_profile);

// Create an execution plan for applying the profile
ProfilePlan plan_profile_application(const Profile& profile, const GenerationContext& ctx);

// Apply a profile to configuration storage
//
// Application phases:
//   1. Validate (check constraints)
//   2. Plan (determine what changes are needed)
//   3. Checkpoint/Backup (if required for recovery)
//   4. Execute (write files, create directories)
//   5. Verify (postconditions checked)
//   6. Record (audit evidence)
//
SetupResult apply_profile(const Profile& profile, const GenerationContext& ctx);

// Load a profile from configuration storage
Profile load_profile(const std::string& config_dir);

// Reapply existing profile (idempotent)
//
// If user modified managed files, merge or warn as appropriate.
//
SetupResult reapply_profile(
    const Profile& original_profile,
    const std::map<std::string, std::string>& current_config,
    const GenerationContext& ctx);

}  // namespace rebuntu::setup::profile