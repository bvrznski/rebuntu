// Unit tests for rebuntu::runtime::settings (Phase 1.5)
//
// Tests Settings model: relatively stable explicit behavioral
// selections/toggles whose value is part of effective Rebuntu configuration.

#include <system/runtime/settings.hpp>

#include <iostream>
#include <string>

namespace {

int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)

}  // namespace

// ============================================================================
// Helper Functions
// ============================================================================

void test_setting_kind_to_string() {
    using namespace rebuntu::runtime::settings;
    
    CHECK(to_string(SettingKind::kToggle) == "toggle");
    CHECK(to_string(SettingKind::kSelection) == "selection");
    CHECK(to_string(SettingKind::kChoice) == "choice");
}

void test_scope_to_string() {
    using namespace rebuntu::runtime::settings;
    
    CHECK(to_string(Scope::kSystem) == "system");
    CHECK(to_string(Scope::kUser) == "user");
    CHECK(to_string(Scope::kSession) == "session");
}

void test_setting_definition_creation() {
    using namespace rebuntu::runtime::settings;
    
    SettingDefinition def;
    def.id = "network.enable_ipv6";
    def.kind = SettingKind::kToggle;
    def.scope = Scope::kSystem;
    def.default_value = "true";
    def.description = "Enable IPv6 networking";
    
    CHECK(def.id == "network.enable_ipv6");
    CHECK(def.kind == SettingKind::kToggle);
    CHECK(def.scope == Scope::kSystem);
    CHECK(def.default_value.has_value());
    CHECK(*def.default_value == "true");
}

void test_settings_schema_basic() {
    using namespace rebuntu::runtime::settings;
    
    SettingsSchema schema;
    
    // Add a toggle setting
    SettingDefinition toggle_def;
    toggle_def.id = "network.enable_ipv6";
    toggle_def.kind = SettingKind::kToggle;
    toggle_def.scope = Scope::kUser;
    toggle_def.default_value = "false";
    toggle_def.description = "Enable IPv6 networking";
    
    schema.add_setting(toggle_def);
    
    // Add a selection setting with allowed values
    SettingDefinition selection_def;
    selection_def.id = "logging.level";
    selection_def.kind = SettingKind::kSelection;
    selection_def.scope = Scope::kUser;
    selection_def.allowed_values = {"debug", "info", "warning", "error"};
    
    schema.add_setting(selection_def);
    
    CHECK(schema.setting_count() == 2);
    CHECK(schema.find("network.enable_ipv6") != nullptr);
    CHECK(schema.find("logging.level") != nullptr);
    CHECK(schema.find("nonexistent") == nullptr);
}

void test_settings_schema_validation() {
    using namespace rebuntu::runtime::settings;
    
    SettingsSchema schema;
    
    SettingDefinition def;
    def.id = "logging.level";
    def.kind = SettingKind::kSelection;
    def.scope = Scope::kUser;
    def.allowed_values = {"debug", "info", "warning", "error"};
    
    schema.add_setting(def);
    
    // Valid values
    CHECK(schema.validate_value(def, "debug") == true);
    CHECK(schema.validate_value(def, "info") == true);
    CHECK(schema.validate_value(def, "critical") == false);
    
    // Validate multiple values
    std::map<std::string, std::string> valid_values = {
        {"logging.level", "warning"}
    };
    auto errors = schema.validate_values(valid_values);
    CHECK(errors.empty());
    
    // Invalid value
    std::map<std::string, std::string> invalid_values = {
        {"logging.level", "critical"}
    };
    errors = schema.validate_values(invalid_values);
    CHECK(!errors.empty());
}

void test_settings_registry() {
    using namespace rebuntu::runtime::settings;
    
    SettingsRegistry registry;
    
    // Add a schema
    SettingsSchema schema;
    SettingDefinition def;
    def.id = "network.enable_ipv6";
    def.kind = SettingKind::kToggle;
    def.scope = Scope::kUser;
    def.default_value = "false";
    schema.add_setting(def);
    
    registry.add_schema("default", std::move(schema));
    
    CHECK(registry.find_schema("default") != nullptr);
    CHECK(registry.find_schema("nonexistent") == nullptr);
}

void test_settings_manager_get_value() {
    using namespace rebuntu::runtime::settings;
    
    SettingsRegistry registry;
    
    // Add a schema with default value
    SettingsSchema schema;
    SettingDefinition def;
    def.id = "network.enable_ipv6";
    def.kind = SettingKind::kToggle;
    def.scope = Scope::kUser;
    def.default_value = "false";
    schema.add_setting(def);
    
    registry.add_schema("default", std::move(schema));
    
    SettingsManager manager(registry);
    
    // Get default value (no user override)
    auto value = manager.get_value("network.enable_ipv6");
    CHECK(value.has_value());
    CHECK(value->id == "network.enable_ipv6");
    CHECK(value->value == "false");
    CHECK(value->is_default == true);
    CHECK(value->source == SettingValue::Source::kDefault);
}

void test_settings_manager_apply_change() {
    using namespace rebuntu::runtime::settings;
    
    SettingsRegistry registry;
    
    // Add a schema
    SettingsSchema schema;
    SettingDefinition def;
    def.id = "network.enable_ipv6";
    def.kind = SettingKind::kToggle;
    def.scope = Scope::kUser;
    def.default_value = "false";
    schema.add_setting(def);
    
    registry.add_schema("default", std::move(schema));
    
    SettingsManager manager(registry);
    
    // Apply a valid change
    SettingChange change;
    change.id = "network.enable_ipv6";
    change.new_value = "true";
    change.target_scope = Scope::kUser;
    
    auto result = manager.apply_change(change);
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
    CHECK((*result.value).id == "network.enable_ipv6");
    CHECK((*result.value).value == "true");
}

void test_settings_manager_apply_invalid_value() {
    using namespace rebuntu::runtime::settings;
    
    SettingsRegistry registry;
    
    // Add a schema with constrained allowed values
    SettingsSchema schema;
    SettingDefinition def;
    def.id = "logging.level";
    def.kind = SettingKind::kSelection;
    def.scope = Scope::kUser;
    def.allowed_values = {"debug", "info", "warning", "error"};
    
    schema.add_setting(def);
    
    registry.add_schema("default", std::move(schema));
    
    SettingsManager manager(registry);
    
    // Try to apply an invalid value
    SettingChange change;
    change.id = "logging.level";
    change.new_value = "critical";  // Not in allowed_values
    
    auto result = manager.apply_change(change);
    CHECK(result.status == rebuntu::core::SemanticStatus::kFailure);
}

void test_settings_manager_apply_unknown_setting() {
    using namespace rebuntu::runtime::settings;
    
    SettingsRegistry registry;
    SettingsSchema schema;
    registry.add_schema("default", std::move(schema));
    
    SettingsManager manager(registry);
    
    // Try to apply a change to an unknown setting
    SettingChange change;
    change.id = "nonexistent.setting";
    change.new_value = "test";
    
    auto result = manager.apply_change(change);
    CHECK(result.status == rebuntu::core::SemanticStatus::kFailure);
}

// ============================================================================
// Main entry points
// ============================================================================

int main_basic_tests() {
    g_failures = 0;
    
    test_setting_kind_to_string();
    test_scope_to_string();
    test_setting_definition_creation();
    test_settings_schema_basic();
    test_settings_registry();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " basic test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_settings_basic: OK\n";
    return 0;
}

int main_validation_tests() {
    g_failures = 0;
    
    test_settings_schema_validation();
    test_settings_manager_get_value();
    test_settings_manager_apply_change();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " validation test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_settings_validation: OK\n";
    return 0;
}

int main_error_tests() {
    g_failures = 0;
    
    test_settings_manager_apply_invalid_value();
    test_settings_manager_apply_unknown_setting();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " error-path test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_settings_error_paths: OK\n";
    return 0;
}

// Full test suite entry point
int main_all() {
    int result = main_basic_tests();
    if (result != 0) return result;
    
    result = main_validation_tests();
    if (result != 0) return result;
    
    result = main_error_tests();
    return result;
}

// Standard main entry point
int main() { return main_all(); }
