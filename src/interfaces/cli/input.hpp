// rebuntu::interfaces::cli::input — Machine-readable command boundary (Task 6.47)

#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <set>
#include <chrono>

namespace rebuntu {
namespace interfaces {
namespace cli {
namespace input {

struct SchemaVersion {
    int major;
    int minor;
    int patch;
    
    std::string to_string() const;
    static SchemaVersion parse(const std::string& sv);
    bool operator==(SchemaVersion other) const;
    bool operator!=(SchemaVersion other) const;
    bool is_compatible_with(SchemaVersion other) const;
};

std::string to_string(SchemaVersion v);

constexpr SchemaVersion kCurrentInputVersion{1, 0, 0};
constexpr const char* kInputSchemaId = "rebuntu.cli.input.v1";

enum class SecurityClassification {
    kPublic,
    kInternal,
    kSensitive,
    kDangerous,
};

struct FieldDefinition {
    std::string name;
    std::string type;
    bool required{false};
    SecurityClassification classification{SecurityClassification::kPublic};
    std::vector<std::string> enum_values;
    std::optional<size_t> max_length;
    std::optional<int64_t> min_value;
    std::optional<int64_t> max_value;
};

enum class ValidationErrorType {
    kUnknownField,
    kMalformedEnum,
    kMissingRequired,
    kInvalidValuePattern,
    kTypeMismatch,
};

struct ValidationError {
    ValidationErrorType type;
    std::string field_name;
    std::string message;
    
    std::string to_string() const;
};

struct InputValidationResult {
    bool valid{false};
    std::vector<ValidationError> errors;
    
    static InputValidationResult success();
    static InputValidationResult failure(const std::string& field, ValidationErrorType type, const std::string& message);
};

struct CommandInput {
    SchemaVersion schema_version{kCurrentInputVersion};
    std::string verb;
    std::optional<std::string> subject_type;
    std::vector<std::string> targets;
    std::map<std::string, std::string> parameters;
    std::vector<std::string> qualifiers;
    bool dry_run{false};
    bool verify{true};
    int max_attempts{1};
    std::chrono::milliseconds timeout{30000};
    std::optional<std::string> caller_id;
    std::optional<std::string> session_id;
    std::optional<std::string> request_id;
    bool security_validated{false};
};

// SecurityFilter - must be defined before InputValidator since validate() uses it
class SecurityFilter {
public:
    std::vector<std::string> find_dangerous_fields(
        const std::map<std::string, std::string>& parameters
    ) const;

    InputValidationResult filter(CommandInput& input) const;
    InputValidationResult check_security(const CommandInput& input) const;
};

class InputValidator {
public:
    InputValidationResult validate(const CommandInput& input) const;
    bool is_security_sensitive_field(const std::string& field_name) const;
    bool contains_forbidden_pattern(const std::string& value) const;
    bool is_valid_enum_value(const std::string& field_name, const std::string& enum_value) const;

private:
    std::optional<FieldDefinition> get_field_def(const std::string& name) const;
    static const std::map<std::string, FieldDefinition>& get_known_fields();
};

namespace serialization {

std::string to_json_string(const CommandInput& input);
InputValidationResult from_json_string(const std::string& json, CommandInput& out_input);

}

bool is_safe_command_verb(const std::string& verb);
bool is_safe_subject_type(const std::string& subject);

const std::set<std::string>& get_security_sensitive_field_names();
const std::set<std::string>& get_forbidden_value_patterns();

}  // namespace input
}  // namespace cli
}  // namespace interfaces
}  // namespace rebuntu

