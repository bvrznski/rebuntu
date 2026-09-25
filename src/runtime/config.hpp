// rebuntu::runtime::config — Configuration & Specification Grammar (Phase 0.18)
//
// This establishes Rebuntu's canonical grammar for declarative configuration
// and specifications.
//
// Core principles:
//   * SPECIFICATION ≠ INSTANCE
//       - Spec = static declaration (TaskDefinition, ServiceConfig)
//       - Instance = runtime occurrence (Job, ServiceInstance)
//   * CONFIGURATION ≠ STATE
//       - Configuration = variable specification applied at init ("WITH WHAT")
//       - State = authoritative runtime-owned data
//   * Preference ≠ Policy
//       - Preference = soft choice that may be unsatisfied
//       - Policy = rules describing what MAY/MUST/SHOULD/MUST NOT happen

#pragma once

#include <system/core/contracts.hpp>
#include <algorithm>
#include <chrono>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::config {

// SourceKind: Where a configuration value originates
enum class SourceKind {
    kDefault,          // Built-in default (deterministic and documented)
    kSystemConfig,     // System-wide configuration
    kHostProfile,      // Host-specific profile
    kUserConfig,       // User-level configuration
    kUserPreference,   // User preferences (soft, may be unsatisfied)
    kEnvironment,      // Environment variables
    kInvocation,       // Invocation-time override
    kPolicyEnforced,   // Policy-enforced value (non-overridable)
};

inline std::string_view to_string(SourceKind s) {
    switch (s) {
        case SourceKind::kDefault:      return "default";
        case SourceKind::kSystemConfig: return "system_config";
        case SourceKind::kHostProfile:  return "host_profile";
        case SourceKind::kUserConfig:   return "user_config";
        case SourceKind::kUserPreference:return "user_preference";
        case SourceKind::kEnvironment:  return "environment";
        case SourceKind::kInvocation:   return "invocation";
        case SourceKind::kPolicyEnforced: return "policy_enforced";
    }
    return "unknown";
}

// ConstraintKind: Types of constraints on configuration values
enum class ConstraintKind {
    kRequired,
    kOptional,
    kConstrained,
    kPolicyEnforced,
};

inline std::string_view to_string(ConstraintKind c) {
    switch (c) {
        case ConstraintKind::kRequired:     return "required";
        case ConstraintKind::kOptional:     return "optional";
        case ConstraintKind::kConstrained:  return "constrained";
        case ConstraintKind::kPolicyEnforced: return "policy_enforced";
    }
    return "unknown";
}

// ValueType: Types of configuration values
enum class ValueType {
    kString, kInteger, kBoolean, kFloat, kEnum, kList, kMap
};

inline std::string_view to_string(ValueType t) {
    switch (t) {
        case ValueType::kString: return "string";
        case ValueType::kInteger: return "integer";
        case ValueType::kBoolean: return "boolean";
        case ValueType::kFloat: return "float";
        case ValueType::kEnum: return "enum";
        case ValueType::kList: return "list";
        case ValueType::kMap: return "map";
    }
    return "unknown";
}

// SchemaDefinition: A typed schema for a configuration value
struct SchemaDefinition {
    std::string name;
    ValueType type = ValueType::kString;
    ConstraintKind constraint = ConstraintKind::kOptional;
    std::optional<std::string> default_value;
    std::optional<int64_t> min_value;
    std::optional<int64_t> max_value;
    std::optional<size_t> min_length;
    std::optional<size_t> max_length;
    std::set<std::string> allowed_values;
    bool allows_override = true;
    std::optional<std::string> description;
};

// Schema: A collection of schema definitions forming a configuration contract
class Schema {
public:
    void add_field(SchemaDefinition def) { fields_[def.name] = std::move(def); }
    
    const SchemaDefinition* find(std::string_view name) const {
        auto it = fields_.find(std::string{name});
        return (it == fields_.end()) ? nullptr : &it->second;
    }
    
    size_t field_count() const { return fields_.size(); }
    
    std::vector<std::string> required_fields() const {
        std::vector<std::string> result;
        for (const auto& [name, def] : fields_) {
            if (def.constraint == ConstraintKind::kRequired ||
                def.constraint == ConstraintKind::kPolicyEnforced) {
                result.push_back(name);
            }
        }
        return result;
    }
    
    std::vector<std::string> all_field_names() const {
        std::vector<std::string> result;
        for (const auto& [name, _] : fields_) result.push_back(name);
        std::sort(result.begin(), result.end());
        return result;
    }
    
    std::vector<std::string> validate(const std::map<std::string, std::string>& config) const {
        std::vector<std::string> errors;
        
        for (const auto& [name, def] : fields_) {
            if ((def.constraint == ConstraintKind::kRequired ||
                 def.constraint == ConstraintKind::kPolicyEnforced) &&
                config.find(name) == config.end()) {
                errors.push_back("missing required field: " + name);
            }
        }
        
        for (const auto& [name, value] : config) {
            auto it = fields_.find(name);
            if (it == fields_.end()) {
                errors.push_back("unknown field: " + name);
                continue;
            }
            
            const auto& def = it->second;
            if (!def.allowed_values.empty() && def.type == ValueType::kEnum) {
                if (def.allowed_values.find(value) == def.allowed_values.end()) {
                    errors.push_back("invalid value for " + name + ": " + value);
                }
            }
        }
        
        return errors;
    }

private:
    std::map<std::string, SchemaDefinition> fields_;
};

// ConfigValue: A configuration value with provenance
struct ConfigValue {
    std::string name;
    std::string value;
    SourceKind source = SourceKind::kDefault;
    std::optional<SourceKind> overridden_source;
    std::optional<std::string> default_value;
    std::vector<std::string> constraints;
};

// Configuration: Complete configuration with values from multiple sources
class Configuration {
public:
    void add_value(std::string name, std::string value, SourceKind source) {
        values_[source][std::move(name)] = std::move(value);
    }
    
    std::optional<ConfigValue> get_effective(const Schema& schema,
                                              std::string_view name) const {
        auto policy_it = values_.find(SourceKind::kPolicyEnforced);
        if (policy_it != values_.end()) {
            auto val_it = policy_it->second.find(std::string{name});
            if (val_it != policy_it->second.end()) {
                ConfigValue cv;
                cv.name = std::string{name};
                cv.value = val_it->second;
                cv.source = SourceKind::kPolicyEnforced;
                return cv;
            }
        }
        
        const std::vector<SourceKind> precedence_order = {
            SourceKind::kInvocation, SourceKind::kEnvironment,
            SourceKind::kUserPreference, SourceKind::kUserConfig,
            SourceKind::kHostProfile, SourceKind::kSystemConfig, SourceKind::kDefault
        };
        
        for (auto source : precedence_order) {
            auto it = values_.find(source);
            if (it != values_.end()) {
                auto val_it = it->second.find(std::string{name});
                if (val_it != it->second.end()) {
                    ConfigValue cv;
                    cv.name = std::string{name};
                    cv.value = val_it->second;
                    cv.source = source;
                    
                    for (int i = 0; i < static_cast<int>(source); ++i) {
                        auto prev_source = static_cast<SourceKind>(i);
                        auto prev_it = values_.find(prev_source);
                        if (prev_it != values_.end() &&
                            prev_it->second.find(std::string{name}) != prev_it->second.end()) {
                            cv.overridden_source = prev_source;
                            break;
                        }
                    }
                    
                    auto field = schema.find(name);
                    if (field && field->default_value.has_value()) {
                        cv.default_value = *field->default_value;
                    }
                    
                    return cv;
                }
            }
        }
        
        return std::nullopt;
    }
    
    bool has_field(std::string_view name) const {
        for (const auto& [source, vals] : values_) {
            if (vals.find(std::string{name}) != vals.end()) return true;
        }
        return false;
    }

    // Get flattened config map for schema validation
    std::map<std::string, std::string> get_all_config_values() const {
        std::map<std::string, std::string> result;
        for (const auto& [source, vals] : values_) {
            for (const auto& [k, v] : vals) {
                result[k] = v;
            }
        }
        return result;
    }

    const std::map<SourceKind, std::map<std::string, std::string>>& all_values() const {
        return values_;
    }

private:
    std::map<SourceKind, std::map<std::string, std::string>> values_;
};

// Preference: A soft preference that may be unsatisfied
struct Preference {
    std::string id;
    std::optional<std::string> title;
    std::optional<std::string> description;
    ValueType type = ValueType::kString;
    std::vector<std::string> preferred_values;
    
    enum class UnmetBehavior { kFallback, kWarn, kError } unmet_behavior = UnmetBehavior::kFallback;
    std::optional<std::string> fallback_value;
};

// PolicyKind: Types of policy rules
enum class PolicyKind {
    kMandatory, kProhibited, kRecommended, kAllowed
};

inline std::string_view to_string(PolicyKind p) {
    switch (p) {
        case PolicyKind::kMandatory:   return "mandatory";
        case PolicyKind::kProhibited:  return "prohibited";
        case PolicyKind::kRecommended: return "recommended";
        case PolicyKind::kAllowed:     return "allowed";
    }
    return "unknown";
}

struct PolicyRule {
    std::string id;
    PolicyKind kind;
    std::optional<std::string> description;
    std::optional<std::string> target_field;
    std::set<std::string> allowed_values;
    bool affects_user_config = true;
    bool affects_system_config = true;
};

// ConfigRegistry: Registry for managing configuration schemas, policies, and preferences
class ConfigRegistry {
public:
    void register_schema(std::string name, Schema schema) {
        schemas_[std::move(name)] = std::move(schema);
    }
    
    const Schema* find_schema(std::string_view name) const {
        auto it = schemas_.find(std::string{name});
        return (it == schemas_.end()) ? nullptr : &it->second;
    }
    
    void add_policy(PolicyRule rule) { policies_.push_back(std::move(rule)); }
    
    std::vector<PolicyRule> get_policies_for_field(std::string_view field) const {
        std::vector<PolicyRule> result;
        for (const auto& policy : policies_) {
            if (policy.target_field && *policy.target_field == field)
                result.push_back(policy);
        }
        return result;
    }
    
    void add_preference(Preference pref) { preferences_.push_back(std::move(pref)); }
    
    std::vector<Preference> get_preferences_for_type(ValueType type) const {
        std::vector<Preference> result;
        for (const auto& pref : preferences_) {
            if (pref.type == type) result.push_back(pref);
        }
        return result;
    }
    
    size_t schema_count() const { return schemas_.size(); }
    const std::map<std::string, Schema>& get_schemas() const { return schemas_; }
    
    // For ConfigLoader validation - expose schemas for iteration
    const std::map<std::string, Schema>& access_schemas() const { return schemas_; }

private:
    std::map<std::string, Schema> schemas_;
    std::vector<PolicyRule> policies_;
    std::vector<Preference> preferences_;
};

// ConfigLoader: Utility for loading configurations from various sources
class ConfigLoader {
public:
    explicit ConfigLoader(ConfigRegistry registry) : registry_(std::move(registry)) {}
    
    void load_from_source(std::string_view name,
                          std::map<std::string, std::string> values,
                          SourceKind source) {
        (void)name;  // suppress unused parameter warning
        for (const auto& [k, v] : values)
            config_.add_value(k, v, source);
    }
    
    core::Result<Configuration> resolve() const {
        std::vector<std::string> errors;
        
        for (const auto& [name, schema] : registry_.access_schemas()) {
            auto validation_errors = schema.validate(config_.get_all_config_values());
            errors.insert(errors.end(), validation_errors.begin(), validation_errors.end());
        }
        
        if (!errors.empty()) {
            core::Result<Configuration> result;
            result.status = core::SemanticStatus::kFailure;
            result.error = core::Error{"E_CONFIG_VALIDATION_ERROR",
                "Configuration validation failed: " + std::to_string(errors.size()) + " errors"};
            return result;
        }
        
        core::Result<Configuration> result;
        result.status = core::SemanticStatus::kSuccess;
        result.value = config_;
        return result;
    }

private:
    ConfigRegistry registry_;
    Configuration config_;
};

// ---------------------------------------------------------------------------
// FormatParser - TOML/JSON/YAML configuration format parsers
//
// These provide parsing for standard configuration formats. Parsing is
 // format-agnostic; the parser output is always a std::map<string, string>
// that can be loaded into a Configuration.
// ---------------------------------------------------------------------------

class FormatParser {
public:
    static core::Result<std::map<std::string, std::string>> parse_toml(std::string_view content) {
        std::map<std::string, std::string> result;
        size_t pos = 0;
        
        while (pos < content.size()) {
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t' || content[pos] == '\n')) {
                if (content[pos] == '#') {
                    while (pos < content.size() && content[pos] != '\n') pos++;
                } else {
                    pos++;
                }
            }
            
            if (pos >= content.size()) break;
            
            size_t key_start = pos;
            while (pos < content.size() && 
                   (isalnum(content[pos]) || content[pos] == '_' || content[pos] == '.')) {
                pos++;
            }
            
            if (pos == key_start) break;
            std::string key(content.substr(key_start, pos - key_start));
            
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t')) pos++;
            
            if (pos >= content.size() || content[pos] != '=') {
                core::Result<std::map<std::string, std::string>> r;
                r.status = core::SemanticStatus::kFailure;
                r.error = core::Error{"E_CONFIG_PARSE_ERROR", "Missing '=' after key: " + key};
                return r;
            }
            pos++;
            
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t')) pos++;
            
            std::string value;
            if (pos < content.size() && content[pos] == '"') {
                pos++;
                size_t value_start = pos;
                while (pos < content.size() && content[pos] != '"') pos++;
                value = std::string(content.substr(value_start, pos - value_start));
                if (pos < content.size()) pos++;
            } else {
                size_t value_start = pos;
                while (pos < content.size() && 
                       (isalnum(content[pos]) || content[pos] == '_')) pos++;
                value = std::string(content.substr(value_start, pos - value_start));
            }
            
            result[std::move(key)] = std::move(value);
        }
        
        core::Result<std::map<std::string, std::string>> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = result;
        return r;
    }

    static core::Result<std::map<std::string, std::string>> parse_json(std::string_view content) {
        std::map<std::string, std::string> result;
        size_t pos = 0;
        
        while (pos < content.size()) {
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t' || content[pos] == '\n')) pos++;
            
            if (pos >= content.size()) break;
            
            if (content[pos] != '"') { pos++; continue; }
            pos++;
            
            size_t key_start = pos;
            while (pos < content.size() && 
                   content[pos] != '"' && content[pos] != '\\') pos++;
            
            std::string key(content.substr(key_start, pos - key_start));
            pos++;
            
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t')) pos++;
            
            if (pos >= content.size() || content[pos] != ':') {
                core::Result<std::map<std::string, std::string>> r;
                r.status = core::SemanticStatus::kFailure;
                r.error = core::Error{"E_CONFIG_PARSE_ERROR", "Missing ':' after key: " + key};
                return r;
            }
            pos++;
            
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t')) pos++;
            
            std::string value;
            if (pos < content.size() && content[pos] == '"') {
                pos++;
                size_t value_start = pos;
                while (pos < content.size() && 
                       content[pos] != '"' && content[pos] != '\\') pos++;
                value = std::string(content.substr(value_start, pos - value_start));
            } else {
                size_t value_start = pos;
                while (pos < content.size() && 
                       (isalnum(content[pos]) || content[pos] == '.')) pos++;
                value = std::string(content.substr(value_start, pos - value_start));
            }
            
            result[std::move(key)] = std::move(value);
        }
        
        core::Result<std::map<std::string, std::string>> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = result;
        return r;
    }

    static core::Result<std::map<std::string, std::string>> parse_env(std::string_view content) {
        std::map<std::string, std::string> result;
        size_t pos = 0;
        
        while (pos < content.size()) {
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t' || content[pos] == '\n')) pos++;
            
            if (pos >= content.size()) break;
            
            size_t key_start = pos;
            while (pos < content.size() && 
                   (isalnum(content[pos]) || content[pos] == '_')) pos++;
            
            if (pos == key_start) { pos++; continue; }
            
            std::string key(content.substr(key_start, pos - key_start));
            
            while (pos < content.size() && 
                   (content[pos] == ' ' || content[pos] == '\t')) pos++;
            
            if (pos >= content.size() || content[pos] != '=') {
                core::Result<std::map<std::string, std::string>> r;
                r.status = core::SemanticStatus::kFailure;
                r.error = core::Error{"E_CONFIG_PARSE_ERROR", "Missing '=' after env var: " + key};
                return r;
            }
            pos++;
            
            size_t value_start = pos;
            while (pos < content.size() && content[pos] != '\n') pos++;
            
            std::string value(content.substr(value_start, pos - value_start));
            
            while (!value.empty() && 
                   (value.back() == ' ' || value.back() == '\t')) value.pop_back();
            
            result[std::move(key)] = std::move(value);
        }
        
        core::Result<std::map<std::string, std::string>> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = result;
        return r;
    }
};

// ---------------------------------------------------------------------------
// WatchHandle - Handle for configuration file watch subscriptions
// ---------------------------------------------------------------------------

class WatchHandle {
public:
    explicit WatchHandle(std::function<void()> callback)
        : callback_(std::move(callback)), active_(true) {}
    
    void fire() { if (active_ && callback_) callback_(); }
    void cancel() { active_ = false; }
    bool is_active() const { return active_; }

private:
    std::function<void()> callback_;
    bool active_;
};

// ---------------------------------------------------------------------------
// ConfigWatcher - Watch/reload mechanism for dynamic configuration changes
// ---------------------------------------------------------------------------

class ConfigWatcher {
public:
    explicit ConfigWatcher(ConfigRegistry registry) : registry_(std::move(registry)) {}
    
    std::shared_ptr<WatchHandle> watch_file(std::string_view path, SourceKind source,
                                             std::function<void(const Configuration&)> on_change) {
        (void)path;  // suppress unused parameter warning
        auto handle = std::make_shared<WatchHandle>([this, source, on_change] {
            auto result = load_from_file(source);
            if (result.status == core::SemanticStatus::kSuccess && result.value.has_value()) {
                config_ = *result.value;
                on_change(config_);
            }
        });
        watches_.push_back(handle);
        return handle;
    }

    std::shared_ptr<WatchHandle> watch_env(std::string_view var_name,
                                            std::function<void(const Configuration&)> on_change) {
        auto handle = std::make_shared<WatchHandle>([this, var_name, on_change] {
            auto result = load_from_env(var_name);
            if (result.status == core::SemanticStatus::kSuccess && result.value.has_value()) {
                config_ = *result.value;
                on_change(config_);
            }
        });
        watches_.push_back(handle);
        return handle;
    }

    void force_reload() { for (const auto& w : watches_) if (w && w->is_active()) w->fire(); }
    const Configuration& config() const { return config_; }

private:
    core::Result<Configuration> load_from_file(SourceKind source) {
        core::Result<Configuration> r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = config_;
        return r;
    }
    
    core::Result<Configuration> load_from_env(std::string_view var_name) {
        if (const char* val = std::getenv(std::string{var_name}.c_str())) {
            Configuration cfg;
            cfg.add_value(std::string{var_name}, val, SourceKind::kEnvironment);
            core::Result<Configuration> r;
            r.status = core::SemanticStatus::kSuccess;
            r.value = cfg;
            return r;
        }
        core::Result<Configuration> r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{"E_CONFIG_ENV_NOT_FOUND", 
                               "Env var not found: " + std::string(var_name)};
        return r;
    }

    ConfigRegistry registry_;
    Configuration config_;
    std::vector<std::shared_ptr<WatchHandle>> watches_;
};

// ---------------------------------------------------------------------------
// Expression - Validation DSL expression types
// ---------------------------------------------------------------------------

enum class ExprType {
    kLiteral, kVariable, kAnd, kOr, kNot,
    kEquals, kNotEquals, kLessThan, kGreaterThan, kInSet, kPattern
};

struct Expression {
    ExprType type;
    std::optional<std::string> literal_value;
    std::vector<Expression> children;
    
    bool evaluate(const Configuration& config, const Schema& schema) const {
        switch (type) {
            case ExprType::kLiteral: return literal_value.has_value();
            case ExprType::kAnd:
                for (const auto& c : children) if (!c.evaluate(config, schema)) return false;
                return true;
            case ExprType::kOr:
                for (const auto& c : children) if (c.evaluate(config, schema)) return true;
                return false;
            default: return false;
        }
    }
};

// ---------------------------------------------------------------------------
// ValidationError - Validation DSL evaluation result
// ---------------------------------------------------------------------------

struct ValidationError {
    std::string message;
    std::vector<std::string> path;
    int line = 0;
};

class ValidationResult {
public:
    static ValidationResult success() { return ValidationResult(true, {}); }
    static ValidationResult failure(std::string msg) {
        return ValidationResult(false, {ValidationError{std::move(msg), {}, 0}});
    }
    
    bool is_valid() const { return valid_; }
    std::vector<ValidationError> errors() const { return errors_; }

private:
    explicit ValidationResult(bool v, std::vector<ValidationError> e)
        : valid_(v), errors_(std::move(e)) {}
    
    bool valid_;
    std::vector<ValidationError> errors_;
};

// ---------------------------------------------------------------------------
// ValidationEngine - Main validation engine using the DSL
// ---------------------------------------------------------------------------

class ValidationEngine {
public:
    ValidationResult validate(const Configuration& config, const Schema& schema) const {
        for (const auto& field_name : schema.required_fields()) {
            if (!config.has_field(field_name)) {
                return ValidationResult::failure("Required field missing: " + field_name);
            }
        }
        
        auto all_values = config.get_all_config_values();
        for (const auto& [field_name, value] : all_values) {
            if (auto def = schema.find(field_name)) {
                try {
                    auto nval = std::stoll(value);
                    if (def->min_value.has_value() && nval < *def->min_value)
                        return ValidationResult::failure("Value below minimum for " + field_name);
                    if (def->max_value.has_value() && nval > *def->max_value)
                        return ValidationResult::failure("Value above maximum for " + field_name);
                } catch (...) {}
            }
        }
        
        return ValidationResult::success();
    }

    ValidationResult validate_with_dsl(const Configuration& config, const Schema& schema,
                                        const Expression& expression) const {
        if (expression.evaluate(config, schema))
            return ValidationResult::success();
        return ValidationResult::failure("DSL constraint not satisfied");
    }
};

}  // namespace rebuntu::runtime::config