// rebuntu::install::forms - Installation forms and structured setup input (Phase 1.3)
// 
// This is Phase 1.3: Enhanced forms with:
// - Unknown field detection
// - Comprehensive path validation (kPathExists, kPathIsDirectory, kPathIsFile)
// - Better error handling and validation messages
#pragma once
#include <system/core/contracts.hpp>
#include <portability/install/contracts.hpp>
#include <any>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <set>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::install::forms {

enum class FieldType {
    kString, kInteger, kBoolean, kEnum, kPath, kChoice, kMultiSelect,
};

inline std::string_view to_string(FieldType t) {
    switch (t) {
        case FieldType::kString: return "string";
        case FieldType::kInteger: return "integer";
        case FieldType::kBoolean: return "boolean";
        case FieldType::kEnum: return "enum";
        case FieldType::kPath: return "path";
        case FieldType::kChoice: return "choice";
        case FieldType::kMultiSelect: return "multiselect";
    }
    return "unknown";
}

enum class ValidationLevel { kInfo, kWarning, kError };

inline std::string_view to_string(ValidationLevel l) {
    switch (l) {
        case ValidationLevel::kInfo: return "info";
        case ValidationLevel::kWarning: return "warning";
        case ValidationLevel::kError: return "error";
    }
    return "unknown";
}

struct FieldConstraint {
    enum class Kind { kRequired, kMinLength, kMaxLength, kMinValue, kMaxValue,
        kPattern, kAllowedValues, kNotAllowedValues, kPathExists, kPathIsDirectory,
        kPathIsFile, kNotEmpty } kind = Kind::kRequired;
    std::optional<int> int_value;
    std::optional<std::string> string_value;
    std::vector<std::string> set_values;
};

struct FieldMetadata {
    std::string name, title, description;
    std::optional<std::string> placeholder;
    bool is_sensitive = false, is_advanced = false;
    enum class ValueSource { kUserProvided, kDetectedHost, kDefault, kSuggested } value_source = ValueSource::kUserProvided;
};

struct FieldResult {
    std::string name;
    bool is_present = false;
    enum class Status { kUnknown, kValid, kInvalid, kMissing, kWarning } status = Status::kUnknown;
    std::optional<std::any> value;
    struct ValidationIssue { ValidationLevel level; std::string code, message; };
    std::vector<ValidationIssue> issues;
    bool is_error() const { return status == Status::kInvalid || status == Status::kMissing; }
};

struct FormResult {
    std::string form_name;
    std::vector<FieldResult> fields;
    bool is_valid() const {
        for (const auto& f : fields) if (f.is_error()) return false;
        return true;
    }
    bool has_warnings() const {
        for (const auto& f : fields) if (f.status == FieldResult::Status::kWarning || !f.issues.empty()) return true;
        return false;
    }
    std::optional<FieldResult> get_field(std::string_view name) const {
        for (const auto& f : fields) if (f.name == name) return f;
        return std::nullopt;
    }
};

struct FieldDefinition { 
    FieldMetadata metadata; 
    FieldType type = FieldType::kString;
    std::vector<FieldConstraint> constraints;
    std::optional<std::vector<std::string>> allowed_values;
    std::optional<std::any> default_value; 
};

struct FormDefinition { 
    std::string name, title, description;
    bool is_interactive = true, requires_all_fields = true;
    std::vector<FieldDefinition> fields; 
};

class InputChannel {
public:
    virtual ~InputChannel() = default;
    virtual std::vector<std::string> available_fields() const = 0;
    virtual bool has_field(std::string_view name) const = 0;
    virtual std::optional<std::string> try_get_string(std::string_view name) const = 0;
    virtual std::map<std::string, std::string> all_values() const = 0;
};

class InteractiveInputChannel : public InputChannel {
public:
    InteractiveInputChannel() = default;
    
    void set_value(std::string n, std::string v) { values_[std::move(n)] = std::move(v); }
    void clear() { values_.clear(); }
    
    std::vector<std::string> available_fields() const override {
        std::vector<std::string> result;
        result.reserve(values_.size());
        for (const auto& [name, _] : values_) result.push_back(name);
        return result;
    }
    
    bool has_field(std::string_view name) const override {
        return values_.find(std::string{name}) != values_.end();
    }
    
    std::optional<std::string> try_get_string(std::string_view name) const override {
        auto it = values_.find(std::string{name});
        return (it != values_.end()) ? std::make_optional(it->second) : std::nullopt;
    }
    
    std::map<std::string, std::string> all_values() const override { return values_; }

private:
    std::map<std::string, std::string> values_;
};

class ConfigFileChannel : public InputChannel {
public:
    explicit ConfigFileChannel(std::map<std::string, std::string> v) : values_(std::move(v)) {}
    
    std::vector<std::string> available_fields() const override {
        std::vector<std::string> result;
        result.reserve(values_.size());
        for (const auto& [name, _] : values_) result.push_back(name);
        return result;
    }
    
    bool has_field(std::string_view name) const override {
        return values_.find(std::string{name}) != values_.end();
    }
    
    std::optional<std::string> try_get_string(std::string_view name) const override {
        auto it = values_.find(std::string{name});
        return (it != values_.end()) ? std::make_optional(it->second) : std::nullopt;
    }
    
    std::map<std::string, std::string> all_values() const override { return values_; }

private:
    std::map<std::string, std::string> values_;
};

class FormParser {
public:
    explicit FormParser(const FormDefinition& def) : definition_(def) {}

    FormResult parse(const InputChannel& channel) const {
        FormResult result;
        result.form_name = definition_.name;
        std::set<std::string> known;
        for (const auto& field_def : definition_.fields) known.insert(field_def.metadata.name);

        // Detect and report unknown fields
        for (const auto& name : channel.available_fields()) {
            if (known.find(name) == known.end()) {
                FieldResult unknown;
                unknown.name = name;
                unknown.is_present = true;
                unknown.status = FieldResult::Status::kInvalid;
                unknown.issues.push_back({ValidationLevel::kError, "E_UNKNOWN_FIELD",
                    "Unknown field '" + name + "'"});
                result.fields.push_back(std::move(unknown));
            }
        }

        for (const auto& field_def : definition_.fields) {
            FieldResult fr;
            fr.name = field_def.metadata.name;
            const bool required = has_constraint(field_def, FieldConstraint::Kind::kRequired);
            
            if (!channel.has_field(field_def.metadata.name)) {
                // Field not provided - check for default or mark as missing
                if (field_def.default_value.has_value()) {
                    fr.value = field_def.default_value;
                    fr.status = FieldResult::Status::kValid;
                } else if (required) {
                    fr.status = FieldResult::Status::kMissing;
                    fr.issues.push_back({ValidationLevel::kError, "E_FIELD_REQUIRED",
                        "Required field is missing"});
                }
                result.fields.push_back(std::move(fr));
                continue;
            }

            fr.is_present = true;
            const std::string raw = channel.try_get_string(field_def.metadata.name).value_or("");
            parse_value(field_def, raw, fr);
            if (!fr.is_error()) validate(field_def, raw, fr);
            result.fields.push_back(std::move(fr));
        }
        return result;
    }

private:
    static bool has_constraint(const FieldDefinition& f, FieldConstraint::Kind k) {
        return std::any_of(f.constraints.begin(), f.constraints.end(),
            [k](const FieldConstraint& c) { return c.kind == k; });
    }

    static void error(FieldResult& fr, std::string code, std::string message) {
        fr.status = FieldResult::Status::kInvalid;
        fr.issues.push_back({ValidationLevel::kError, std::move(code), std::move(message)});
    }

    static void parse_value(const FieldDefinition& f, const std::string& raw, FieldResult& fr) {
        try {
            switch (f.type) {
                case FieldType::kInteger: {
                    std::size_t used = 0;
                    auto value = std::stoll(raw, &used);
                    if (used != raw.size()) throw std::invalid_argument("trailing");
                    fr.value = static_cast<int64_t>(value);
                    break;
                }
                case FieldType::kBoolean: {
                    std::string v = raw;
                    std::transform(v.begin(), v.end(), v.begin(),
                        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                    if (v == "true" || v == "yes" || v == "1") fr.value = true;
                    else if (v == "false" || v == "no" || v == "0") fr.value = false;
                    else { error(fr, "E_INVALID_BOOLEAN", "Expected boolean value"); return; }
                    break;
                }
                default: fr.value = raw; break;
            }
            fr.status = FieldResult::Status::kValid;
        } catch (...) {
            error(fr, "E_INVALID_INTEGER", "Expected integer value");
        }
    }

    static void validate(const FieldDefinition& f, const std::string& raw, FieldResult& fr) {
        // Check against allowed values
        if (f.allowed_values.has_value() &&
            std::find(f.allowed_values->begin(), f.allowed_values->end(), raw) == f.allowed_values->end()) {
            error(fr, "E_VALUE_NOT_ALLOWED", "Value is not an admissible option");
            return;
        }
        
        // Apply additional constraints
        for (const auto& c : f.constraints) {
            switch (c.kind) {
                case FieldConstraint::Kind::kNotEmpty:
                    if (raw.empty()) error(fr, "E_EMPTY", "Value must not be empty");
                    break;
                case FieldConstraint::Kind::kMinLength:
                    if (c.int_value && raw.size() < static_cast<std::size_t>(*c.int_value))
                        error(fr, "E_MIN_LENGTH", "Value is shorter than allowed");
                    break;
                case FieldConstraint::Kind::kMaxLength:
                    if (c.int_value && raw.size() > static_cast<std::size_t>(*c.int_value))
                        error(fr, "E_MAX_LENGTH", "Value is longer than allowed");
                    break;
                case FieldConstraint::Kind::kPathExists:
                    if (!std::filesystem::exists(raw)) error(fr, "E_PATH_MISSING", "Path does not exist");
                    break;
                case FieldConstraint::Kind::kPathIsDirectory:
                    if (!std::filesystem::is_directory(raw)) error(fr, "E_PATH_NOT_DIRECTORY", "Path is not a directory");
                    break;
                case FieldConstraint::Kind::kPathIsFile:
                    if (!std::filesystem::is_regular_file(raw)) error(fr, "E_PATH_NOT_FILE", "Path is not a regular file");
                    break;
                default: break;
            }
            if (fr.is_error()) return;
        }
    }

    const FormDefinition& definition_;
};

class FormBuilder {
public:
    static FormBuilder create(std::string n, std::string t) { return FormBuilder{n, t}; }
    
    FormBuilder& add_string_field(std::string n, std::string t, std::string d) {
        FieldDefinition f; f.type = FieldType::kString;
        f.metadata.name = std::move(n); f.metadata.title = std::move(t);
        f.metadata.description = std::move(d);
        definition_.fields.push_back(f);
        return *this;
    }
    
    FormBuilder& add_integer_field(std::string n, std::string t, std::string d) {
        FieldDefinition f; f.type = FieldType::kInteger;
        f.metadata.name = std::move(n); f.metadata.title = std::move(t);
        f.metadata.description = std::move(d);
        definition_.fields.push_back(f);
        return *this;
    }
    
    FormBuilder& add_boolean_field(std::string n, std::string t, std::string d) {
        FieldDefinition f; f.type = FieldType::kBoolean;
        f.metadata.name = std::move(n); f.metadata.title = std::move(t);
        f.metadata.description = std::move(d);
        definition_.fields.push_back(f);
        return *this;
    }
    
    FormBuilder& add_enum_field(std::string n, std::string t, std::string d,
            std::vector<std::string> allowed) {
        FieldDefinition f; f.type = FieldType::kEnum;
        f.allowed_values = std::move(allowed);
        f.metadata.name = std::move(n); f.metadata.title = std::move(t);
        f.metadata.description = std::move(d);
        definition_.fields.push_back(f);
        return *this;
    }
    
    FormBuilder& add_path_field(std::string n, std::string t, std::string d) {
        FieldDefinition f; f.type = FieldType::kPath;
        f.metadata.name = std::move(n); f.metadata.title = std::move(t);
        f.metadata.description = std::move(d);
        definition_.fields.push_back(f);
        return *this;
    }
    
    FormBuilder& set_interactive(bool v) { definition_.is_interactive = v; return *this; }
    
    FormDefinition build() {
        FormDefinition r = std::move(definition_);
        definition_ = FormDefinition{};
        return r;
    }

private:
    explicit FormBuilder(std::string n, std::string t) {
        definition_.name = std::move(n);
        definition_.title = std::move(t);
    }
    FormDefinition definition_;
};

class InstallationFormFactory {
public:
    static FormDefinition create_installation_intent_form() {
        return FormBuilder::create("installation_intent", "Installation Intent")
            .add_string_field("version", "Version", "Target version to install (e.g., 1.0.0)")
            .add_enum_field("scope", "Scope", "System or user installation", {"system", "user"})
            .add_boolean_field("skip_verification", "Skip Verification", 
                "If true, skip verification during installation (not recommended)")
            .build();
    }
    
    static FormDefinition create_scope_selection_form() {
        return FormBuilder::create("scope_selection", "Installation Scope")
            .add_enum_field("scope", "Scope", "System or user installation", {"system", "user"})
            .build();
    }
    
    static FormDefinition create_feature_selection_form() {
        return FormBuilder::create("feature_selection", "Feature Selection")
            .add_string_field("features", "Features", "Comma-separated list of optional features")
            .build();
    }

private:
    InstallationFormFactory() = delete;
};

}  // namespace rebuntu::install::forms