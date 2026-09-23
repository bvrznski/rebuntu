// rebuntu::runtime::settings — Settings Model (Phase 1.5)
//
// This establishes Rebuntu's canonical grammar for settings: relatively stable
// explicit behavioral selections/toggles whose value is part of effective
// Rebuntu configuration.
//
// Core principles:
//   * Setting ≠ State
//       - Setting = explicit behavioral toggle/selection (desired state)
//       - State = authoritative runtime-owned data (observed state)
//   * Setting ≠ Option
//       - Setting = WHETHER an action occurs (boolean-like: on/off, enabled/disabled)
//       - Option = WHAT alternative to select from mutually exclusive choices
//   * Setting ≠ Preference
//       - Setting = hard requirement or explicit toggle
//       - Preference = soft choice that may be unsatisfied

#pragma once

#include <runtime/core/contracts.hpp>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <optional>
#include <vector>

namespace rebuntu::runtime::settings {

// SettingKind: Types of settings
enum class SettingKind {
    kToggle,      // Boolean-like: enabled/disabled, on/off
    kSelection,   // One from mutually exclusive set of values
    kChoice,      // Multiple from a set (bitmask-like)
};

inline std::string_view to_string(SettingKind kind) {
    switch (kind) {
        case SettingKind::kToggle:     return "toggle";
        case SettingKind::kSelection:  return "selection";
        case SettingKind::kChoice:     return "choice";
    }
    return "unknown";
}

// Scope: Where the setting applies
enum class Scope {
    kSystem,      // System-wide setting (requires privilege to modify)
    kUser,        // Per-user setting
    kSession,     // Per-session setting (transient)
};

inline std::string_view to_string(Scope scope) {
    switch (scope) {
        case Scope::kSystem: return "system";
        case Scope::kUser:   return "user";
        case Scope::kSession:return "session";
    }
    return "unknown";
}

// SettingDefinition: A typed setting specification
struct SettingDefinition {
    std::string id;                     // Unique identifier (e.g., "network.enable_ipv6")
    
    SettingKind kind = SettingKind::kToggle;
    Scope scope = Scope::kSystem;
    
    std::optional<std::string> description;
    
    // Default value(s) - depends on kind
    std::optional<std::string> default_value;       // For toggle/selection
    
    // Allowed values for Selection and Choice kinds
    std::set<std::string> allowed_values;
    
    // Constraint: whether this setting can be overridden by user
    bool allows_override = true;
    
    // Whether the setting affects security/requires privilege escalation review
    bool is_security_sensitive = false;
    
    // Deprecated options - if present in allowed_values, mark them as deprecated
    std::set<std::string> deprecated_values;
    
    // Option availability condition - options are available when this condition is met
    // Format: "other_setting_id=desired_value"
    std::optional<std::string> availability_condition;
};

// SettingValue: A concrete setting value with provenance
struct SettingValue {
    std::string id;                     // Setting identifier
    std::string value;                  // Current effective value
    
    Scope scope = Scope::kSystem;
    std::optional<Scope> overridden_scope;
    
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
};

// SettingChange: A mutation request for a setting
struct SettingChange {
    std::string id;         // Which setting to change
    std::string new_value;  // The new value
    
    Scope target_scope = Scope::kUser;  // Where to apply the change
    bool verify_immediately = true;     // Whether to verify postcondition after change
    
    // Optional: reason for the change (for audit/evidence)
    std::optional<std::string> justification;
};

// SettingsSchema: A collection of setting definitions forming a contract
class SettingsSchema {
public:
    void add_setting(SettingDefinition def) { 
        settings_[def.id] = std::move(def); 
    }
    
    const SettingDefinition* find(std::string_view id) const {
        auto it = settings_.find(std::string{id});
        return (it == settings_.end()) ? nullptr : &it->second;
    }
    
    size_t setting_count() const { return settings_.size(); }
    
    std::vector<std::string> all_setting_ids() const {
        std::vector<std::string> result;
        for (const auto& [id, _] : settings_) result.push_back(id);
        return result;
    }
    
    // Validate a setting value against its definition
    bool validate_value(const SettingDefinition& def, const std::string& value) const {
        if (def.allowed_values.empty()) return true;  // No constraint
        
        return def.allowed_values.find(value) != def.allowed_values.end();
    }
    
    // Validate all values in a map against the schema
    std::vector<std::string> validate_values(
        const std::map<std::string, std::string>& values) const {
        std::vector<std::string> errors;
        
        for (const auto& [id, value] : values) {
            auto it = settings_.find(id);
            if (it == settings_.end()) {
                errors.push_back("unknown setting: " + id);
                continue;
            }
            
            const auto& def = it->second;
            if (!validate_value(def, value)) {
                std::string allowed;
                for (const auto& v : def.allowed_values) {
                    if (!allowed.empty()) allowed += ", ";
                    allowed += v;
                }
                errors.push_back("invalid value for " + id + ": '" + value + 
                                 "', must be one of: [" + allowed + "]");
            }
        }
        
        return errors;
    }

private:
    std::map<std::string, SettingDefinition> settings_;
};

// SettingsRegistry: Registry for managing settings schemas and values
class SettingsRegistry {
public:
    void add_schema(std::string name, SettingsSchema schema) {
        schemas_[std::move(name)] = std::move(schema);
    }
    
    const SettingsSchema* find_schema(std::string_view name) const {
        auto it = schemas_.find(std::string{name});
        return (it == schemas_.end()) ? nullptr : &it->second;
    }
    
    // Add a setting value to the registry
    void add_value(std::string id, SettingValue value) {
        values_[std::move(id)] = std::move(value);
    }
    
    // Get effective value for a setting, considering precedence
    std::optional<SettingValue> get_effective(const SettingsSchema& schema,
                                               std::string_view id) const {
        auto it = values_.find(std::string{id});
        if (it != values_.end()) return it->second;
        
        // Check default from schema
        auto def = schema.find(id);
        if (def && def->default_value.has_value()) {
            SettingValue value;
            value.id = std::string{id};
            value.value = *def->default_value;
            value.scope = def->scope;
            value.source = SettingValue::Source::kDefault;
            value.is_default = true;
            return value;
        }
        
        return std::nullopt;
    }
    
    // Get all setting values
    const std::map<std::string, SettingValue>& all_values() const { return values_; }

private:
    std::map<std::string, SettingsSchema> schemas_;
    std::map<std::string, SettingValue> values_;
};

// SettingsManager: High-level interface for managing settings mutations
class SettingsManager {
public:
    explicit SettingsManager(SettingsRegistry registry)
        : registry_(std::move(registry)) {}
    
    // Get effective value of a setting
    std::optional<SettingValue> get_value(std::string_view id) const {
        auto schema = registry_.find_schema("default");
        if (!schema) return std::nullopt;
        return registry_.get_effective(*schema, id);
    }
    
    // Get all settings values
    std::map<std::string, SettingValue> get_all_values() const {
        auto schema = registry_.find_schema("default");
        std::map<std::string, SettingValue> result;
        
        for (const auto& [id, value] : registry_.all_values()) {
            if (!value.is_default) result[id] = value;
        }
        
        // Add defaults
        if (schema) {
            for (const auto& id : schema->all_setting_ids()) {
                if (result.find(id) == result.end()) {
                    if (auto v = registry_.get_effective(*schema, id)) {
                        result[id] = *v;
                    }
                }
            }
        }
        
        return result;
    }
    
    // Apply a setting change
    core::Result<SettingValue> apply_change(const SettingChange& change) const {
        auto schema = registry_.find_schema("default");
        if (!schema) {
            core::Result<SettingValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_SETTINGS_SCHEMA_NOT_FOUND", "No default schema registered"};
            return r;
        }
        
        auto def = schema->find(change.id);
        if (!def) {
            core::Result<SettingValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_SETTINGS_UNKNOWN_SETTING", "Unknown setting: " + change.id};
            return r;
        }
        
        // Validate the new value
        if (!schema->validate_value(*def, change.new_value)) {
            core::Result<SettingValue> r;
            r.status = core::SemanticStatus::kFailure;
            std::string allowed;
            for (const auto& v : def->allowed_values) {
                if (!allowed.empty()) allowed += ", ";
                allowed += v;
            }
            r.error = core::Error{"E_SETTINGS_INVALID_VALUE", 
                                  "Invalid value for " + change.id + ": must be one of [" + allowed + "]"};
            return r;
        }
        
        // Check scope constraints (user can't modify system-only settings)
        if (def->scope == Scope::kSystem && !false) {
            core::Result<SettingValue> r;
            r.status = core::SemanticStatus::kFailure;
            r.error = core::Error{"E_SETTINGS_SCOPE_VIOLATION", 
                                  "Cannot modify system-only setting from user context"};
            return r;
        }
        
        // Create the new value (in real implementation, this would write to config)
        SettingValue new_value;
        new_value.id = change.id;
        new_value.value = change.new_value;
        new_value.scope = change.target_scope;
        new_value.source = SettingValue::Source::kUserConfig;
        new_value.is_default = false;
        
        // For now, just return success - in real implementation would persist
        core::Result<SettingValue> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = new_value;
        return r;
    }
    
    // Apply multiple changes atomically (best effort)
    std::vector<core::Result<SettingValue>> apply_changes(
        const std::vector<SettingChange>& changes) const {
        std::vector<core::Result<SettingValue>> results;
        for (const auto& change : changes) {
            results.push_back(apply_change(change));
        }
        return results;
    }

private:
    SettingsRegistry registry_;
};

}  // namespace rebuntu::runtime::settings
