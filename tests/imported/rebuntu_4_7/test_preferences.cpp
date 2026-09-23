// Unit tests for rebuntu::runtime::preferences (Phase 1.7)
//
// Tests Preferences model: soft choices that guide Rebuntu behavior without
// pretending they are guaranteed system state.

#include <system/runtime/preferences.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace {

int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)

}  // namespace

// ============================================================================
// Helper Functions
// ============================================================================

void test_preference_satisfaction_to_string() {
    using rebuntu::runtime::preferences::to_string;
    using rebuntu::runtime::preferences::PreferenceSatisfaction;
    
    CHECK(to_string(PreferenceSatisfaction::SATISFIED) == "satisfied");
    CHECK(to_string(PreferenceSatisfaction::UNSATISFIED) == "unsatisfied");
    CHECK(to_string(PreferenceSatisfaction::NOT_APPLICABLE) == "not_applicable");
    CHECK(to_string(PreferenceSatisfaction::UNKNOWN) == "unknown");
}

void test_preference_scope_to_string() {
    using rebuntu::runtime::preferences::to_string;
    using rebuntu::runtime::preferences::PreferenceScope;
    
    CHECK(to_string(PreferenceScope::kSystem) == "system");
    CHECK(to_string(PreferenceScope::kUser) == "user");
    CHECK(to_string(PreferenceScope::kSession) == "session");
}

void test_preference_type_to_string() {
    using rebuntu::runtime::preferences::to_string;
    using rebuntu::runtime::preferences::PreferenceType;
    
    CHECK(to_string(PreferenceType::kSelection) == "selection");
    CHECK(to_string(PreferenceType::kChoice) == "choice");
    CHECK(to_string(PreferenceType::kToggle) == "toggle");
}

void test_unmet_behavior_to_string() {
    using rebuntu::runtime::preferences::to_string;
    using rebuntu::runtime::preferences::UnmetBehavior;
    
    CHECK(to_string(UnmetBehavior::kFallback) == "fallback");
    CHECK(to_string(UnmetBehavior::kWarn) == "warn");
    CHECK(to_string(UnmetBehavior::kError) == "error");
}

void test_preference_definition_creation() {
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def.title = "Preferred Provider";
    def.description = "Select the preferred provider for operations";
    def.default_value = "systemd";
    def.preferred_values = {"systemd", "docker", "podman"};
    def.fallback_value = "systemd";
    
    CHECK(def.id == "provider.preferred");
    CHECK(def.type == rebuntu::runtime::preferences::PreferenceType::kSelection);
    CHECK(def.scope == rebuntu::runtime::preferences::PreferenceScope::kUser);
    CHECK(def.title.has_value());
    CHECK(def.default_value.has_value());
    CHECK(!def.preferred_values.empty());
}

// ============================================================================
// PreferencesSchema Tests
// ============================================================================

void test_preferences_schema_basic() {
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferencesSchema schema;
    
    // Add a preference with selection type
    PreferenceDefinition def1;
    def1.id = "provider.preferred";
    def1.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def1.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def1.default_value = "systemd";
    def1.preferred_values = {"systemd", "docker", "podman"};
    
    schema.add_preference(def1);
    
    // Add a preference with choice type
    PreferenceDefinition def2;
    def2.id = "logging.features";
    def2.type = rebuntu::runtime::preferences::PreferenceType::kChoice;
    def2.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def2.default_value = "debug,trace";
    def2.preferred_values = {"debug", "trace", "info"};
    
    schema.add_preference(def2);
    
    CHECK(schema.preference_count() == 2);
    CHECK(schema.find("provider.preferred") != nullptr);
    CHECK(schema.find("logging.features") != nullptr);
    CHECK(schema.find("nonexistent") == nullptr);
}

void test_preferences_schema_preferred_value_selection() {
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferencesSchema schema;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman", "systemd"};
    
    schema.add_preference(def);
    
    // Test get_effective_preferred - should select first available preferred value
    std::vector<std::string> available1 = {"docker", "some-other"};
    auto result1 = schema.get_effective_preferred(def, available1);
    CHECK(result1.has_value());
    CHECK(*result1 == "docker");
    
    // Test with podman only (higher preference than systemd)
    std::vector<std::string> available2 = {"podman", "other"};
    auto result2 = schema.get_effective_preferred(def, available2);
    CHECK(result2.has_value());
    CHECK(*result2 == "podman");
    
    // Test with no preferred values - should fall back to default
    std::vector<std::string> available3 = {"other", "another"};
    auto result3 = schema.get_effective_preferred(def, available3);
    CHECK(result3.has_value());
    CHECK(*result3 == "systemd");  // fallback
}

void test_preferences_schema_preferred_no_fallback() {
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferencesSchema schema;
    
    PreferenceDefinition def;
    def.id = "editor.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    // No default, no fallback
    def.preferred_values = {"vim", "nvim"};
    
    schema.add_preference(def);
    
    // Test with no available matching preferred values and no fallback
    std::vector<std::string> available = {"emacs", "nano"};
    auto result = schema.get_effective_preferred(def, available);
    CHECK(!result.has_value());  // Should return nullopt when nothing matches
}

// ============================================================================
// PreferencesRegistry Tests
// ============================================================================

void test_preferences_registry_basic() {
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferencesRegistry registry;
    
    // Add a schema
    PreferencesSchema schema;
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    
    schema.add_preference(def);
    
    registry.add_schema("default", std::move(schema));
    
    CHECK(registry.find_schema("default") != nullptr);
    CHECK(registry.find_schema("nonexistent") == nullptr);
}

void test_preferences_registry_get_effective() {
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    using rebuntu::runtime::preferences::PreferencesManager;
    
    PreferencesRegistry registry;
    
    // Add a schema
    PreferencesSchema schema;
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    
    schema.add_preference(def);
    
    registry.add_schema("default", std::move(schema));
    
    // Get default value (no user override)
    PreferencesManager manager(registry);
    auto result = manager.get_value("provider.preferred", {"docker"});
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
}

void test_preferences_registry_get_unknown_preference() {
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferencesManager;
    
    PreferencesRegistry registry;
    PreferencesSchema schema;
    registry.add_schema("default", std::move(schema));
    
    PreferencesManager manager(registry);
    auto result = manager.get_value("nonexistent.preference", {});
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kFailure);
}

// ============================================================================
// PreferenceEvaluator Tests
// ============================================================================

void test_preference_evaluator_satisfied() {
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    
    // Available values include docker (highest preference)
    std::vector<std::string> available = {"docker", "podman"};
    auto result = rebuntu::runtime::preferences::PreferenceEvaluator::evaluate_satisfaction(def, available);
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);  // found a satisfying option
    CHECK(*result.value == rebuntu::runtime::preferences::PreferenceSatisfaction::SATISFIED);
}

void test_preference_evaluator_unsatisfied() {
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    
    // Available values don't match any preferred
    std::vector<std::string> available = {"other", "another"};
    auto result = rebuntu::runtime::preferences::PreferenceEvaluator::evaluate_satisfaction(def, available);
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kCompleted);  // evaluation completed but no satisfaction found
    CHECK(*result.value == rebuntu::runtime::preferences::PreferenceSatisfaction::UNSATISFIED);
}

void test_preference_evaluator_not_applicable() {
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.default_value = "systemd";
    def.preferred_values = {"docker"};
    
    // No available values
    std::vector<std::string> available = {};
    auto result = rebuntu::runtime::preferences::PreferenceEvaluator::evaluate_satisfaction(def, available);
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);  // evaluation completed successfully with NOT_APPLICABLE
    CHECK(*result.value == rebuntu::runtime::preferences::PreferenceSatisfaction::NOT_APPLICABLE);
}

void test_preference_evaluator_get_satisfying_options() {
    using rebuntu::runtime::preferences::PreferenceDefinition;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    
    std::vector<std::string> available = {"podman", "other", "docker"};
    auto result = rebuntu::runtime::preferences::PreferenceEvaluator::get_satisfying_options(def, available);
    
    // Should return docker first (highest preference), then podman
    CHECK(!result.empty());
    CHECK(result[0] == "docker");
}

// ============================================================================
// PreferenceChange Tests
// ============================================================================

void test_preference_change_validation() {
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    using rebuntu::runtime::preferences::UnmetBehavior;
    using rebuntu::runtime::preferences::PreferenceChange;
    using rebuntu::runtime::preferences::PreferencesManager;
    
    PreferencesRegistry registry;
    PreferencesSchema schema;
    
    // Test with kError - should reject invalid values
    {
        PreferenceDefinition def;
        def.id = "provider.preferred";
        def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
        def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
        def.default_value = "systemd";
        def.preferred_values = {"docker", "podman"};
        def.unmet_behavior = UnmetBehavior::kError;  // strict mode
        
        schema.add_preference(def);
    }
    
    registry.add_schema("default", std::move(schema));
    
    PreferencesManager manager(registry);
    
    // Valid change - docker is in preferred values
    PreferenceChange change1;
    change1.id = "provider.preferred";
    change1.new_values = {"docker"};
    auto result1 = manager.apply_change(change1);
    
    CHECK(result1.status == rebuntu::core::SemanticStatus::kSuccess);
    
    // Invalid change - "invalid" is not in preferred values
    PreferenceChange change2;
    change2.id = "provider.preferred";
    change2.new_values = {"invalid"};
    auto result2 = manager.apply_change(change2);
    
    CHECK(result2.status == rebuntu::core::SemanticStatus::kFailure);
}

// ============================================================================
// Integration Tests
// ============================================================================

void test_preferences_full_workflow() {
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesManager;
    
    // Create schema with multiple preferences
    PreferencesSchema schema;
    
    PreferenceDefinition provider_def;
    provider_def.id = "provider.preferred";
    provider_def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    provider_def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    provider_def.default_value = "systemd";
    provider_def.preferred_values = {"docker", "podman"};
    provider_def.fallback_value = "systemd";
    
    schema.add_preference(provider_def);
    
    PreferencesRegistry registry;
    registry.add_schema("default", std::move(schema));
    
    // Test with docker available
    {
        PreferencesManager manager(registry);
        auto result = manager.get_value("provider.preferred", {"docker"});
        
        CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
    }
    
    // Test with no available preferred values
    {
        PreferencesManager manager(registry);
        auto result = manager.get_value("provider.preferred", {"other"});
        
        // Should still succeed but be unsatisfied (uses fallback)
        CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
    }
}

void test_preferences_precedence() {
    using rebuntu::runtime::preferences::PreferencesRegistry;
    using rebuntu::runtime::preferences::PreferencesSchema;
    using rebuntu::runtime::preferences::PreferenceDefinition;
    using rebuntu::runtime::preferences::PreferenceValue;
    using rebuntu::runtime::preferences::PreferencesManager;
    
    PreferencesRegistry registry;
    PreferencesSchema schema;
    
    PreferenceDefinition def;
    def.id = "provider.preferred";
    def.type = rebuntu::runtime::preferences::PreferenceType::kSelection;
    def.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    def.default_value = "systemd";
    def.preferred_values = {"docker", "podman"};
    def.fallback_value = "systemd";
    
    schema.add_preference(def);
    registry.add_schema("default", std::move(schema));
    
    // Add user-configured value
    PreferenceValue pref_value;
    pref_value.id = "provider.preferred";
    pref_value.selected_value = "docker";
    pref_value.scope = rebuntu::runtime::preferences::PreferenceScope::kUser;
    pref_value.source = PreferenceValue::Source::kUserConfig;
    pref_value.is_default = false;
    
    registry.add_value("provider.preferred", std::move(pref_value));
    
    PreferencesManager manager(registry);
    auto result = manager.get_value("provider.preferred", {"docker"});
    
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
}

// ============================================================================
// Main entry points
// ============================================================================

int main_basic_tests() {
    g_failures = 0;
    
    test_preference_satisfaction_to_string();
    test_preference_scope_to_string();
    test_preference_type_to_string();
    test_unmet_behavior_to_string();
    test_preference_definition_creation();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " basic test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_basic: OK\n";
    return 0;
}

int main_schema_tests() {
    g_failures = 0;
    
    test_preferences_schema_basic();
    test_preferences_schema_preferred_value_selection();
    test_preferences_schema_preferred_no_fallback();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " schema test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_schema: OK\n";
    return 0;
}

int main_registry_tests() {
    g_failures = 0;
    
    test_preferences_registry_basic();
    test_preferences_registry_get_effective();
    test_preferences_registry_get_unknown_preference();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " registry test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_registry: OK\n";
    return 0;
}

int main_evaluator_tests() {
    g_failures = 0;
    
    test_preference_evaluator_satisfied();
    test_preference_evaluator_unsatisfied();
    test_preference_evaluator_not_applicable();
    test_preference_evaluator_get_satisfying_options();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " evaluator test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_evaluator: OK\n";
    return 0;
}

int main_change_tests() {
    g_failures = 0;
    
    test_preference_change_validation();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " change test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_change: OK\n";
    return 0;
}

int main_integration_tests() {
    g_failures = 0;
    
    test_preferences_full_workflow();
    test_preferences_precedence();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " integration test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_preferences_integration: OK\n";
    return 0;
}

// Full test suite entry point
int main_all() {
    int result = main_basic_tests();
    if (result != 0) return result;
    
    result = main_schema_tests();
    if (result != 0) return result;
    
    result = main_registry_tests();
    if (result != 0) return result;
    
    result = main_evaluator_tests();
    if (result != 0) return result;
    
    result = main_change_tests();
    if (result != 0) return result;
    
    result = main_integration_tests();
    return result;
}

// Standard main entry point
int main() { return main_all(); }