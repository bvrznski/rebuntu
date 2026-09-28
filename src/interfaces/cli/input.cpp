// rebuntu::interfaces::cli::input — Machine-readable command boundary implementation (Task 6.47)

#include "interfaces/cli/input.hpp"

namespace rebuntu {
namespace interfaces {
namespace cli {
namespace input {

// ============================================================================
// Helper predicates
// ============================================================================

bool is_safe_command_verb(const std::string& verb) {
    static const std::set<std::string> kSafeVerbs = {
        "install", "remove", "update", "query", "status",
        "start", "stop", "restart", "enable", "disable",
        "copy", "move", "delete", "create", "read",
        "mount", "umount", "format", "check",
    };
    return kSafeVerbs.count(verb) > 0;
}

bool is_safe_subject_type(const std::string& subject) {
    static const std::set<std::string> kSafeSubjects = {
        "package", "service", "file", "directory",
        "process", "user", "group",
        "network_interface", "mount_point", "disk",
    };
    return kSafeSubjects.count(subject) > 0;
}

const std::set<std::string>& get_security_sensitive_field_names() {
    static const std::set<std::string> kSecuritySensitiveFields = {
        "shell", "bash", "sh", "command", "exec", "system",
        "run_command", "execute_command", "eval", "script",
        "file_path", "path", "target_path", "destination",
        "source_file", "target_file", "write_path", "output_path",
        "environment", "env", "LD_PRELOAD", "DYLD_LIBRARY_PATH",
        "sudo", "root", "elevate", "privilege", "capability",
        "url", "endpoint", "remote_host", "target_ip",
        "code", "expression", "template", "format_string",
    };
    return kSecuritySensitiveFields;
}

const std::set<std::string>& get_forbidden_value_patterns() {
    static const std::set<std::string> kForbiddenPatterns = {
        "$(", "${", "`", "||", "&&", ";", "|", "&>",
        "..", "/etc/passwd", "/etc/shadow",
        "/bin/sh", "/bin/bash", "/usr/bin/env",
    };
    return kForbiddenPatterns;
}

// ============================================================================
// SchemaVersion
// ============================================================================

std::string SchemaVersion::to_string() const {
    return std::to_string(major) + "." +
           std::to_string(minor) + "." +
           std::to_string(patch);
}

SchemaVersion SchemaVersion::parse(const std::string& sv) {
    SchemaVersion v{1, 0, 0};
    size_t dot1 = sv.find('.');
    if (dot1 != std::string::npos) {
        v.major = std::stoi(sv.substr(0, dot1));
        size_t dot2 = sv.find('.', dot1 + 1);
        if (dot2 != std::string::npos) {
            v.minor = std::stoi(sv.substr(dot1 + 1, dot2 - dot1 - 1));
            v.patch = std::stoi(sv.substr(dot2 + 1));
        } else {
            v.minor = std::stoi(sv.substr(dot1 + 1));
        }
    }
    return v;
}

bool SchemaVersion::operator==(SchemaVersion other) const {
    return major == other.major && minor == other.minor && patch == other.patch;
}

bool SchemaVersion::operator!=(SchemaVersion other) const {
    return !(*this == other);
}

bool SchemaVersion::is_compatible_with(SchemaVersion other) const {
    return major == other.major;
}

std::string to_string(SchemaVersion v) {
    return v.to_string();
}

// ============================================================================
// ValidationError
// ============================================================================

std::string ValidationError::to_string() const {
    std::string result = "ValidationError{";
    result += "type=";
    result += std::to_string(static_cast<int>(type));
    result += ", field=";
    result += field_name;
    result += ", message=\"";
    result += message;
    result += "\"}";
    return result;
}

InputValidationResult InputValidationResult::success() {
    InputValidationResult r;
    r.valid = true;
    return r;
}

InputValidationResult InputValidationResult::failure(const std::string& field, ValidationErrorType type, const std::string& message) {
    InputValidationResult r;
    r.errors.push_back({type, field, message});
    return r;
}

// ============================================================================
// SecurityFilter
// ============================================================================

std::vector<std::string> SecurityFilter::find_dangerous_fields(
    const std::map<std::string, std::string>& parameters
) const {
    std::vector<std::string> dangerous;
    const std::set<std::string>& sensitive = get_security_sensitive_field_names();
    
    for (const auto& param : parameters) {
        if (sensitive.count(param.first) > 0) {
            dangerous.push_back(param.first);
        }
    }
    
    return dangerous;
}

InputValidationResult SecurityFilter::filter(CommandInput& input) const {
    InputValidationResult result;
    result.valid = true;
    return result;
}

InputValidationResult SecurityFilter::check_security(const CommandInput& input) const {
    InputValidationResult result;
    result.valid = true;
    return result;
}

// ============================================================================
// InputValidator
// ============================================================================

std::optional<FieldDefinition> InputValidator::get_field_def(const std::string& name) const {
    static const std::map<std::string, FieldDefinition> kKnownFields = {
        {"verb", {"verb", "string", true, SecurityClassification::kPublic}},
        {"subject_type", {"subject_type", "string", false, SecurityClassification::kPublic}},
        {"targets", {"targets", "array[string]", true, SecurityClassification::kPublic}},
        {"parameters", {"parameters", "map[string]string", false, SecurityClassification::kInternal}},
        {"qualifiers", {"qualifiers", "array[string]", false, SecurityClassification::kPublic}},
        {"dry_run", {"dry_run", "bool", false, SecurityClassification::kPublic}},
        {"verify", {"verify", "bool", false, SecurityClassification::kPublic}},
        {"max_attempts", {"max_attempts", "int", false, SecurityClassification::kInternal}},
        {"timeout", {"timeout", "int (milliseconds)", false, SecurityClassification::kInternal}},
        {"caller_id", {"caller_id", "string", false, SecurityClassification::kInternal}},
        {"session_id", {"session_id", "string", false, SecurityClassification::kInternal}},
        {"request_id", {"request_id", "string", false, SecurityClassification::kInternal}},
    };
    
    auto it = kKnownFields.find(name);
    if (it == kKnownFields.end()) {
        return std::nullopt;
    }
    return it->second;
}

const std::map<std::string, FieldDefinition>& InputValidator::get_known_fields() {
    static const std::map<std::string, FieldDefinition> kKnownFields = {
        {"verb", {"verb", "string", true, SecurityClassification::kPublic}},
        {"subject_type", {"subject_type", "string", false, SecurityClassification::kPublic}},
        {"targets", {"targets", "array[string]", true, SecurityClassification::kPublic}},
        {"parameters", {"parameters", "map[string]string", false, SecurityClassification::kInternal}},
        {"qualifiers", {"qualifiers", "array[string]", false, SecurityClassification::kPublic}},
        {"dry_run", {"dry_run", "bool", false, SecurityClassification::kPublic}},
        {"verify", {"verify", "bool", false, SecurityClassification::kPublic}},
        {"max_attempts", {"max_attempts", "int", false, SecurityClassification::kInternal}},
        {"timeout", {"timeout", "int (milliseconds)", false, SecurityClassification::kInternal}},
        {"caller_id", {"caller_id", "string", false, SecurityClassification::kInternal}},
        {"session_id", {"session_id", "string", false, SecurityClassification::kInternal}},
        {"request_id", {"request_id", "string", false, SecurityClassification::kInternal}},
    };
    return kKnownFields;
}

bool InputValidator::is_security_sensitive_field(const std::string& field_name) const {
    const std::set<std::string>& sensitive = get_security_sensitive_field_names();
    return sensitive.count(field_name) > 0;
}

bool InputValidator::contains_forbidden_pattern(const std::string& value) const {
    const std::set<std::string>& patterns = get_forbidden_value_patterns();
    
    for (const std::string& pattern : patterns) {
        if (value.find(pattern) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool InputValidator::is_valid_enum_value(const std::string& field_name, const std::string& enum_value) const {
    std::optional<FieldDefinition> def = get_field_def(field_name);
    if (!def.has_value()) {
        return false;
    }
    
    const std::vector<std::string>& enum_values = def->enum_values;
    if (enum_values.empty()) {
        return true;
    }
    
    for (const std::string& ev : enum_values) {
        if (ev == enum_value) {
            return true;
        }
    }
    return false;
}

InputValidationResult InputValidator::validate(const CommandInput& input) const {
    InputValidationResult result;
    
    // Validate schema version compatibility
    if (!input.schema_version.is_compatible_with(kCurrentInputVersion)) {
        result.errors.push_back({
            ValidationErrorType::kTypeMismatch,
            "schema_version",
            "Schema version not compatible"
        });
    }
    
    // Validate verb is present and safe
    if (input.verb.empty()) {
        result.errors.push_back({
            ValidationErrorType::kMissingRequired,
            "verb",
            "Verb is required"
        });
    } else if (!is_safe_command_verb(input.verb)) {
        result.errors.push_back({
            ValidationErrorType::kInvalidValuePattern,
            "verb",
            "Verb not in whitelist of safe verbs"
        });
    }
    
    // Validate subject_type if present
    if (input.subject_type.has_value()) {
        std::string subj = *input.subject_type;
        if (!subj.empty() && !is_safe_subject_type(subj)) {
            result.errors.push_back({
                ValidationErrorType::kInvalidValuePattern,
                "subject_type",
                "Subject type not in whitelist"
            });
        }
    }
    
    // Validate targets are present
    if (input.targets.empty()) {
        result.errors.push_back({
            ValidationErrorType::kMissingRequired,
            "targets",
            "At least one target is required"
        });
    } else {
        for (size_t i = 0; i < input.targets.size(); ++i) {
            const std::string& target = input.targets[i];
            if (target.empty()) {
                result.errors.push_back({
                    ValidationErrorType::kInvalidValuePattern,
                    "targets[" + std::to_string(i) + "]",
                    "Target cannot be empty"
                });
            }
        }
    }
    
    // Check for security-sensitive fields in parameters
    SecurityFilter filter;
    auto dangerous_fields = filter.find_dangerous_fields(input.parameters);
    for (const std::string& field : dangerous_fields) {
        result.errors.push_back({
            ValidationErrorType::kUnknownField,
            field,
            "Security-sensitive or unknown field rejected"
        });
    }
    
    // Check all string values for forbidden patterns
    std::vector<std::string> all_strings_to_check;
    all_strings_to_check.push_back(input.verb);
    if (input.subject_type.has_value()) {
        all_strings_to_check.push_back(*input.subject_type);
    }
    for (const std::string& target : input.targets) {
        all_strings_to_check.push_back(target);
    }
    for (const auto& param : input.parameters) {
        all_strings_to_check.push_back(param.second);
    }
    
    const std::set<std::string>& patterns = get_forbidden_value_patterns();
    for (const std::string& s : all_strings_to_check) {
        for (const std::string& pattern : patterns) {
            if (s.find(pattern) != std::string::npos) {
                result.errors.push_back({
                    ValidationErrorType::kInvalidValuePattern,
                    "value",
                    "Contains forbidden pattern"
                });
                break;  // Only report once per string
            }
        }
    }
    
    result.valid = result.errors.empty();
    return result;
}

// ============================================================================
// Serialization
// ============================================================================

namespace serialization {

std::string to_json_string(const CommandInput& input) {
    (void)input;  // Suppress unused parameter warning
    return "{}";
}

InputValidationResult from_json_string(const std::string& json, CommandInput& out_input) {
    (void)json;  // Suppress unused parameter warning
    InputValidationResult r;
    r.valid = true;
    return r;
}

}  // namespace serialization

// ============================================================================
// hash specialization - must be at global scope
// ============================================================================

}  // namespace input
}  // namespace cli
}  // namespace interfaces
}  // namespace rebuntu

namespace std {

template<> 
struct hash<rebuntu::interfaces::cli::input::SchemaVersion> {
    size_t operator()(const rebuntu::interfaces::cli::input::SchemaVersion& v) const noexcept {
        size_t h = 0;
        h ^= std::hash<int>{}(v.major) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int>{}(v.minor) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int>{}(v.patch) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

}  // namespace std