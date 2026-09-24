// rebuntu::runtime::config - Phase 0.18 Configuration & Specification Grammar tests
//
// Tests canonical definitions for:
//   - SourceKind enum (configuration value provenance)
//   - ConstraintKind enum (value constraints)
//   - ValueType enum (configuration types)
//   - SchemaDefinition and Schema classes (typed configuration contracts)
//   - ConfigValue struct with provenance tracking
//   - Configuration class with precedence-based resolution

#include <runtime/config.hpp>
#include <cassert>
#include <iostream>
#include <string>

using namespace rebuntu::runtime::config;

void test_source_kind() {
    // Test SourceKind enum values
    assert(to_string(SourceKind::kDefault) == "default");
    assert(to_string(SourceKind::kSystemConfig) == "system_config");
    assert(to_string(SourceKind::kHostProfile) == "host_profile");
    assert(to_string(SourceKind::kUserConfig) == "user_config");
    assert(to_string(SourceKind::kUserPreference) == "user_preference");
    assert(to_string(SourceKind::kEnvironment) == "environment");
    assert(to_string(SourceKind::kInvocation) == "invocation");
    assert(to_string(SourceKind::kPolicyEnforced) == "policy_enforced");
}

void test_constraint_kind() {
    // Test ConstraintKind enum values
    assert(to_string(ConstraintKind::kRequired) == "required");
    assert(to_string(ConstraintKind::kOptional) == "optional");
    assert(to_string(ConstraintKind::kConstrained) == "constrained");
    assert(to_string(ConstraintKind::kPolicyEnforced) == "policy_enforced");
}

void test_value_type() {
    // Test ValueType enum values
    assert(to_string(ValueType::kString) == "string");
    assert(to_string(ValueType::kInteger) == "integer");
    assert(to_string(ValueType::kBoolean) == "boolean");
    assert(to_string(ValueType::kFloat) == "float");
    assert(to_string(ValueType::kEnum) == "enum");
    assert(to_string(ValueType::kList) == "list");
    assert(to_string(ValueType::kMap) == "map");
}

void test_schema_definition() {
    // Test SchemaDefinition creation
    SchemaDefinition def;
    def.name = "test.field";
    def.type = ValueType::kString;
    def.constraint = ConstraintKind::kOptional;
    def.default_value = "default_value";
    
    assert(def.name == "test.field");
    assert(def.type == ValueType::kString);
    assert(def.constraint == ConstraintKind::kOptional);
    assert(def.default_value.has_value());
    assert(*def.default_value == "default_value");
}

void test_schema() {
    // Test Schema creation and field management
    Schema schema;
    
    schema.add_field({
        .name = "gpu.primary",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kOptional,
        .default_value = "auto"
    });
    
    schema.add_field({
        .name = "timeout.seconds",
        .type = ValueType::kInteger,
        .constraint = ConstraintKind::kRequired
    });
    
    // Test find - use string_view directly in the call
    const SchemaDefinition* found = schema.find("gpu.primary");
    assert(found != nullptr);
    assert(found->default_value.has_value());
    assert(*found->default_value == "auto");
    
    // Test field_count
    assert(schema.field_count() == 2);
    
    // Test required_fields
    auto required = schema.required_fields();
    assert(required.size() == 1);
    assert(required[0] == "timeout.seconds");
}

void test_schema_validation() {
    Schema schema;
    schema.add_field({
        .name = "required_field",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kRequired
    });
    
    schema.add_field({
        .name = "optional_field",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kOptional,
        .default_value = "default"
    });
    
    // Valid config with required field only
    std::map<std::string, std::string> valid_config = {
        {"required_field", "value"}
    };
    auto errors = schema.validate(valid_config);
    assert(errors.empty());
    
    // Config with unknown field should error
    std::map<std::string, std::string> invalid_config = {
        {"required_field", "value"},
        {"unknown_field", "bad"}
    };
    errors = schema.validate(invalid_config);
    assert(!errors.empty());
}

void test_configuration() {
    Configuration config;
    
    // Add values from different sources
    config.add_value("gpu.primary", "nvidia", SourceKind::kUserConfig);
    config.add_value("gpu.primary", "auto", SourceKind::kDefault);
    
    Schema schema;
    schema.add_field({
        .name = "gpu.primary",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kOptional,
        .default_value = "auto"
    });
    
    // Test get_effective - user config should take precedence over default
    auto effective = config.get_effective(schema, "gpu.primary");
    assert(effective.has_value());
    assert(effective->value == "nvidia");
    assert(effective->source == SourceKind::kUserConfig);
}

void test_config_registry() {
    ConfigRegistry registry;
    
    Schema schema;
    schema.add_field({
        .name = "test.field",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kOptional
    });
    
    registry.register_schema("test", std::move(schema));
    
    const Schema* found = registry.find_schema("test");
    assert(found != nullptr);
    assert(registry.schema_count() == 1);
}

void test_config_loader() {
    ConfigRegistry registry;
    
    // Add a simple schema
    Schema schema;
    schema.add_field({
        .name = "test.field",
        .type = ValueType::kString,
        .constraint = ConstraintKind::kOptional,
        .default_value = "default_val"
    });
    registry.register_schema("test", std::move(schema));
    
    ConfigLoader loader(std::move(registry));
    
    // Load from user config source
    std::map<std::string, std::string> values = {
        {"test.field", "user_value"}
    };
    loader.load_from_source("user_config", values, SourceKind::kUserConfig);
    
    // Resolve and check validation - Result has status and error members
    auto result = loader.resolve();
    assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
}

void test_format_parser() {
    // Test TOML parsing
    std::string toml_content = R"(
key1 = "value1"
key2 = "value2"
)";
    
    auto toml_result = FormatParser::parse_toml(toml_content);
    assert(toml_result.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(toml_result.value.size() == 2);
    assert(toml_result.value["key1"] == "value1");
}

void test_preference() {
    Preference pref;
    pref.id = "provider.preferred";
    pref.type = ValueType::kString;
    pref.preferred_values = {"nvidia", "amd"};
    pref.unmet_behavior = Preference::UnmetBehavior::kFallback;
    
    assert(pref.id == "provider.preferred");
    assert(pref.preferred_values.size() == 2);
}

void test_policy_rule() {
    PolicyRule rule;
    rule.id = "policy.1";
    rule.kind = PolicyKind::kMandatory;
    rule.target_field = "gpu.primary";
    rule.allowed_values.insert("nvidia");
    rule.allowed_values.insert("amd");
    
    assert(rule.id == "policy.1");
    assert(to_string(rule.kind) == "mandatory");
}

void test_policy_kind() {
    // Test PolicyKind enum values
    assert(to_string(PolicyKind::kMandatory) == "mandatory");
    assert(to_string(PolicyKind::kProhibited) == "prohibited");
    assert(to_string(PolicyKind::kRecommended) == "recommended");
    assert(to_string(PolicyKind::kAllowed) == "allowed");
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 0.18 Configuration & Specification Grammar tests...\n";
    
    test_source_kind();
    test_constraint_kind();
    test_value_type();
    test_schema_definition();
    test_schema();
    test_schema_validation();
    test_configuration();
    test_config_registry();
    test_config_loader();
    test_format_parser();
    test_preference();
    test_policy_rule();
    test_policy_kind();
    
    std::cout << "All tests PASSED!\n";
    return 0;
}