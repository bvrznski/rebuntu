// rebuntu::runtime::preferences — Preferences Model (Phase 1.7)
//
// This establishes Rebuntu's canonical grammar for user preferences: soft
// choices that guide Rebuntu behavior without pretending they are guaranteed
// system state.
//
// Core principles:
//   * Preference ≠ Policy
//       - Preference = soft choice that may be unsatisfied
//       - Policy = rules describing what MAY/MUST/SHOULD/MUST NOT happen
//   * Preference ≠ Observed State
//       - Preference = user-desired choice (desired state)
//       - Observed State = authoritative runtime-owned data
//   * Preference ≠ Hard Invariant
//       - Preference = may be unsatisfied due to environment/policy/capability

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <optional>
#include <vector>

namespace rebuntu::runtime::preferences {

// PreferenceSatisfaction: Status of preference satisfaction
enum class PreferenceSatisfaction {
    SATISFIED,        // preference is satisfied (choice available and selected)
    UNSATISFIED,      // preference cannot be satisfied (no fallback available)
    NOT_APPLICABLE,   // preference does not apply in current context
    UNKNOWN,          // satisfaction status could not be determined
};

inline std::string_view to_string(PreferenceSatisfaction s) {
    switch (s) {
        case PreferenceSatisfaction::SATISFIED:     return "satisfied";
        case PreferenceSatisfaction::UNSATISFIED:   return "unsatisfied";
        case PreferenceSatisfaction::NOT_APPLICABLE:return "not_applicable";
        case PreferenceSatisfaction::UNKNOWN:       return "unknown";
    }
    return "unknown";
}

// PreferenceScope: Where the preference applies
enum class PreferenceScope {
    kSystem,      // System-wide preference (requires privilege to modify)
    kUser,        // Per-user preference
    kSession,     // Per-session preference (transient)
};

inline std::string_view to_string(PreferenceScope scope) {
    switch (scope) {
        case PreferenceScope::kSystem: return "system";
        case PreferenceScope::kUser:   return "user";
        case PreferenceScope::kSession:return "session";
    }
    return "unknown";
}

// PreferenceType: Types of preferences
enum class PreferenceType {
    kSelection,   // One from mutually exclusive set
    kChoice,      // Multiple from a set
    kToggle,      // Boolean-like preference (enabled/disabled)
};

inline std::string_view to_string(PreferenceType type) {
    switch (type) {
        case PreferenceType::kSelection: return "selection";
        case PreferenceType::kChoice:    return "choice";
        case PreferenceType::kToggle:    return "toggle";
    }
    return "unknown";
}

// UnmetBehavior: What happens when a preference cannot be satisfied
enum class UnmetBehavior {
    kFallback,  // Use fallback value if available
    kWarn,      // Log warning but continue with default
    kError,     // Fail when preference cannot be satisfied
};

inline std::string_view to_string(UnmetBehavior b) {
    switch (b) {
        case UnmetBehavior::kFallback: return "fallback";
        case UnmetBehavior::kWarn:     return "warn";
        case UnmetBehavior::kError:    return "error";
    }
    return "unknown";
}

// PreferenceDefinition: A typed preference specification
struct PreferenceDefinition {
    std::string id;                     // Unique identifier (e.g., "provider.preferred")
    
    PreferenceType type = PreferenceType::kSelection;
    PreferenceScope scope = PreferenceScope::kUser;
    
    std::optional<std::string> title;           // Human-readable title
    std::optional<std::string> description;     // Detailed description
    
    // Default value(s) when preference is not set
    std::optional<std::string> default_value;
    
    // Preferred values (in order of preference)
    std::vector<std::string> preferred_values;
    
    // Fallback behavior when no preferred value is available
    UnmetBehavior unmet_behavior = UnmetBehavior::kFallback;
    std::optional<std::string> fallback_value;
    
    // Whether this preference can be overridden by user config
    bool allows_override = true;
    
    // Constraint: whether this preference affects security
    bool is_security_sensitive = false;
    
    // Availability condition - preference applies when this condition is met
    // Format: "other_setting_id=desired_value"
    std::optional<std::string> availability_condition;
};

// PreferenceValue: A concrete preference value with provenance and satisfaction status
struct PreferenceValue {
    std::string id;                     // Preference identifier
    
    // Current effective value (selected from preferred_values or fallback)
    std::string selected_value;
    
    PreferenceScope scope = PreferenceScope::kUser;
    std::optional<PreferenceScope> overridden_scope;
    
    bool is_default = false;
    std::optional<std::string> default_value;
    
    // Where this value came from (precedence order)
    enum class Source {
        kDefault,
        kSystemConfig,
        kUserConfig,
        kInvocation,      // Command-line override
        kEnvironment,     // Environment variable override
        kPolicyEnforced   // Non-overridable policy-enforced value
    } source = Source::kDefault;
    
    std::optional<Source> overridden_source;
    
    // Satisfaction status of this preference
    PreferenceSatisfaction satisfaction_status = PreferenceSatisfaction::UNKNOWN;
    
    // Reason for dissatisfaction (if not satisfied)
    std::optional<std::string> unsatisfied_reason;
};

// PreferenceChange: A mutation request for a preference
struct PreferenceChange {
    std::string id;             // Which preference to change
    std::vector<std::string> new_values;  // New preferred values
    
    PreferenceScope target_scope = PreferenceScope::kUser;
    bool verify_immediately = true;     // Whether to verify postcondition after change
    
    // Optional: reason for the change (for audit/evidence)
    std::optional<std::string> justification;
};

// PreferencesSchema: A collection of preference definitions forming a contract
class PreferencesSchema {
public:
    void add_preference(PreferenceDefinition def) { 
        preferences_[def.id] = std::move(def); 
    }
    
    const PreferenceDefinition* find(std::string_view id) const {
        auto it = preferences_.find(std::string{id});
        return (it == preferences_.end()) ? nullptr : &it->second;
    }
    
    size_t preference_count() const { return preferences_.size(); }
    
    std::vector<std::string> all_preference_ids() const {
        std::vector<std::string> result;
        for (const auto& [id, _] : preferences_) result.push_back(id);
        return result;
    }
    
    // Check if a value is among the preferred values
    bool contains_preferred_value(const PreferenceDefinition& def, 
                                   const std::string& value) const {
        for (const auto& pref : def.preferred_values) {
            if (pref == value) return true;
        }
        return false;
    }
    
    // Get effective preferred value(s) based on what's available
    std::optional<std::string> get_effective_preferred(
        const PreferenceDefinition& def,
        const std::vector<std::string>& available_values) const {
        
        if (def.preferred_values.empty()) {
            return def.default_value;
        }
        
        for (const auto& preferred : def.preferred_values) {
            for (const auto& available : available_values) {
                if (preferred == available) {
                    return preferred;
                }
            }
        }
        
        // No preferred value found among available values
        // Try fallback first, then default
        if (def.fallback_value.has_value()) {
            return def.fallback_value;
        }
        if (def.default_value.has_value()) {
            return def.default_value;
        }
        return std::nullopt;
    }

private:
    std::map<std::string, PreferenceDefinition> preferences_;
};

// PreferencesRegistry: Registry for managing preferences schemas and values
class PreferencesRegistry {
public:
    void add_schema(std::string name, PreferencesSchema schema) {
        schemas_[std::move(name)] = std::move(schema);
    }
    
    const PreferencesSchema* find_schema(std::string_view name) const {
        auto it = schemas_.find(std::string{name});
        return (it == schemas_.end()) ? nullptr : &it->second;
    }
    
    // Add a preference value to the registry
    void add_value(std::string id, PreferenceValue value) {
        values_[std::move(id)] = std::move(value);
    }
    
    // Get effective value for a preference, considering precedence and satisfaction
    core::Result<PreferenceValue> get_effective(
        const PreferencesSchema& schema,
        std::string_view id,
        const std::vector<std::string>& available_values) const {
        
        auto it = values_.find(std::string{id});
        if (it != values_.end()) {
            PreferenceValue result = it->second;
            
            // Recalculate satisfaction status based on available values
            result.satisfaction_status = calculate_satisfaction(
                schema, id, available_values, result.selected_value);
            
            return core::Result<PreferenceValue>::success(result);
        }
        
        // Check default from schema
        auto def = schema.find(id);
        if (def) {
            PreferenceValue value;
            value.id = std::string{id};
            
            // Get effective preferred value
            auto effective = schema.get_effective_preferred(*def, available_values);
            if (effective.has_value()) {
                value.selected_value = *effective;
                value.satisfaction_status = calculate_satisfaction(
                    schema, id, available_values, value.selected_value);
            } else {
                value.selected_value = "";
                value.satisfaction_status = PreferenceSatisfaction::UNSATISFIED;
                value.unsatisfied_reason = "No preferred or fallback value available";
            }
            
            value.scope = def->scope;
            value.source = PreferenceValue::Source::kDefault;
            value.is_default = true;
            
            return core::Result<PreferenceValue>::success(value);
        }
        
        // Preference not found
        core::Result<PreferenceValue> r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{"E_PREFERENCES_UNKNOWN", "Unknown preference: " + std::string{id}};
        return r;
    }
    
    // Calculate satisfaction status for a preference value
    PreferenceSatisfaction calculate_satisfaction(
        const PreferencesSchema& schema,
        std::string_view pref_id,
        const std::vector<std::string>& available_values,
        const std::string& selected_value) const {
        
        if (available_values.empty()) {
            return PreferenceSatisfaction::NOT_APPLICABLE;
        }
        
        // Check if selected value is among preferred
        auto def = schema.find(pref_id);
        if (!def) {
            return PreferenceSatisfaction::UNKNOWN;
        }
        
        for (const auto& pref : def->preferred_values) {
            if (pref == selected_value) {
                // Found in preferred values
                for (const auto& avail : available_values) {
                    if (avail == selected_value) {
                        return PreferenceSatisfaction::SATISFIED;
                    }
                }
                // In preferred but not available -> unsatisfied
                return PreferenceSatisfaction::UNSATISFIED;
            }
        }
        
        // Check if it's the fallback value
        if (def->fallback_value.has_value() && 
            def->fallback_value.value() == selected_value) {
            return PreferenceSatisfaction::SATISFIED;  // Fallback satisfies
        }
        
        // Default value - check against available
        for (const auto& avail : available_values) {
            if (avail == selected_value) {
                return PreferenceSatisfaction::SATISFIED;
            }
        }
        
        return PreferenceSatisfaction::NOT_APPLICABLE;
    }
    
    // Get all preference values
    const std::map<std::string, PreferenceValue>& all_values() const { 
        return values_; 
    }

private:
    std::map<std::string, PreferencesSchema> schemas_;
    std::map<std::string, PreferenceValue> values_;
};

// PreferencesManager: High-level interface for managing preferences
class PreferencesManager {
public:
    explicit PreferencesManager(PreferencesRegistry registry)
        : registry_(std::move(registry)) {}
    
    // Get effective value of a preference
    core::Result<PreferenceValue> get_value(
        std::string_view id,
        const std::vector<std::string>& available_values) const {
        auto schema = registry_.find_schema("default");
        if (!schema) {
            core::Result<PreferenceValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_PREFERENCES_SCHEMA_NOT_FOUND", 
                                  "No default schema registered"};
            return r;
        }
        return registry_.get_effective(*schema, id, available_values);
    }
    
    // Apply a preference change
    core::Result<PreferenceValue> apply_change(const PreferenceChange& change) const {
        auto schema = registry_.find_schema("default");
        if (!schema) {
            core::Result<PreferenceValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_PREFERENCES_SCHEMA_NOT_FOUND", 
                                  "No default schema registered"};
            return r;
        }
        
        auto def = schema->find(change.id);
        if (!def) {
            core::Result<PreferenceValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_PREFERENCES_UNKNOWN", 
                                  "Unknown preference: " + change.id};
            return r;
        }
        
        // Validate the new values
        if (!validate_values(*def, change.new_values)) {
            core::Result<PreferenceValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_PREFERENCES_INVALID_VALUES", 
                                  "Invalid values for preference: " + change.id};
            return r;
        }
        
        // Create the new value
        PreferenceValue new_value;
        new_value.id = change.id;
        if (!change.new_values.empty()) {
            new_value.selected_value = change.new_values[0];  // Primary selection
        }
        new_value.scope = change.target_scope;
        new_value.source = PreferenceValue::Source::kUserConfig;
        new_value.is_default = false;
        
        core::Result<PreferenceValue> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = new_value;
        return r;
    }
    
    // Check if a set of values is valid for a preference definition
    bool validate_values(const PreferenceDefinition& def,
                         const std::vector<std::string>& values) const {
        // For Selection type, only first value matters
        // For Choice type, multiple values allowed
        if (def.preferred_values.empty()) return true;  // No constraint
        
        for (const auto& v : values) {
            bool found = false;
            for (const auto& pref : def.preferred_values) {
                if (pref == v) {
                    found = true;
                    break;
                }
            }
            if (!found && def.unmet_behavior != UnmetBehavior::kError) {
                // Allow non-preferred values if not in error mode
                continue;
            }
            if (!found) {
                return false;
            }
        }
        
        return !values.empty();
    }

private:
    PreferencesRegistry registry_;
};

// PreferenceEvaluator: Utility for evaluating preference satisfaction
class PreferenceEvaluator {
public:
    // Evaluate satisfaction of a preference given available options
    static core::Result<PreferenceSatisfaction> evaluate_satisfaction(
        const PreferenceDefinition& def,
        const std::vector<std::string>& available_options) {
        
        if (available_options.empty()) {
            return core::Result<PreferenceSatisfaction>::success(
                PreferenceSatisfaction::NOT_APPLICABLE);
        }
        
        // Check each preferred value
        for (const auto& pref : def.preferred_values) {
            for (const auto& avail : available_options) {
                if (pref == avail) {
                    return core::Result<PreferenceSatisfaction>::success(
                        PreferenceSatisfaction::SATISFIED);
                }
            }
        }
        
        // No preferred value found
        if (def.fallback_value.has_value()) {
            for (const auto& avail : available_options) {
                if (*def.fallback_value == avail) {
                    return core::Result<PreferenceSatisfaction>::success(
                        PreferenceSatisfaction::SATISFIED);
                }
            }
        }
        
        // Check if default value is available
        if (def.default_value.has_value()) {
            for (const auto& avail : available_options) {
                if (*def.default_value == avail) {
                    return core::Result<PreferenceSatisfaction>::success(
                        PreferenceSatisfaction::SATISFIED);
                }
            }
        }
        
        // Could not satisfy preference
        std::string reason = "No matching preferred, fallback, or default value found";
        if (!def.preferred_values.empty()) {
            reason += ". Preferred: ";
            for (size_t i = 0; i < def.preferred_values.size(); ++i) {
                if (i > 0) reason += ", ";
                reason += def.preferred_values[i];
            }
        }
        
        // Return success result with satisfaction status
        return core::Result<PreferenceSatisfaction>::ok(PreferenceSatisfaction::UNSATISFIED);
    }
    
    // Get all available options that satisfy the preference (in order)
    static std::vector<std::string> get_satisfying_options(
        const PreferenceDefinition& def,
        const std::vector<std::string>& available_options) {
        
        std::set<std::string> satisfying;
        
        // Preferred values first (in order)
        for (const auto& pref : def.preferred_values) {
            for (const auto& avail : available_options) {
                if (pref == avail) {
                    satisfying.insert(pref);
                    break;
                }
            }
        }
        
        // Fallback value
        if (def.fallback_value.has_value()) {
            for (const auto& avail : available_options) {
                if (*def.fallback_value == avail) {
                    satisfying.insert(*def.fallback_value);
                    break;
                }
            }
        }
        
        return std::vector<std::string>(satisfying.begin(), satisfying.end());
    }
};

}  // namespace rebuntu::runtime::preferences
