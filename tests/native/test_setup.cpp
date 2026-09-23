// Unit tests for rebuntu::setup (Phase 1.8)
//
// Tests Setup & Configuration Machinery:
//   * Setup = initial environment state after installation
//   * Configuration = variable parameters applied at initialization

#include <portability/setup/contracts.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace {
    int g_failures = 0;
    #define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}  // namespace

// ============================================================================
// SetupPhase Tests
// ============================================================================

void test_setup_phase_to_string() {
    using rebuntu::setup::to_string;
    using rebuntu::setup::SetupPhase;
    
    CHECK(to_string(SetupPhase::kNotStarted) == "not_started");
    CHECK(to_string(SetupPhase::kInProgress) == "in_progress");
    CHECK(to_string(SetupPhase::kComplete) == "complete");
    CHECK(to_string(SetupPhase::kFailed) == "failed");
    CHECK(to_string(SetupPhase::kDegraded) == "degraded");
}

// ============================================================================
// ConfigurationSource Tests
// ============================================================================

void test_configuration_source_to_string() {
    using rebuntu::setup::to_string;
    using rebuntu::setup::ConfigurationSource;
    
    CHECK(to_string(ConfigurationSource::kDefault) == "default");
    CHECK(to_string(ConfigurationSource::kSystemConfig) == "system_config");
    CHECK(to_string(ConfigurationSource::kUserConfig) == "user_config");
    CHECK(to_string(ConfigurationSource::kEnvironment) == "environment");
    CHECK(to_string(ConfigurationSource::kOverride) == "override");
}

// ============================================================================
// ConfigurationMode Tests
// ============================================================================

void test_configuration_mode_to_string() {
    using rebuntu::setup::to_string;
    using rebuntu::setup::ConfigurationMode;
    
    CHECK(to_string(ConfigurationMode::kStandard) == "standard");
    CHECK(to_string(ConfigurationMode::kStrict) == "strict");
    CHECK(to_string(ConfigurationMode::kPermissive) == "permissive");
}

// ============================================================================
// SetupArtifact Tests
// ============================================================================

void test_setup_artifact_creation() {
    using rebuntu::setup::SetupArtifact;
    
    SetupArtifact artifact;
    artifact.name = "config_directory";
    artifact.path = "/etc/rebuntu";
    artifact.is_required = true;
    
    CHECK(artifact.name == "config_directory");
    CHECK(artifact.path == "/etc/rebuntu");
    CHECK(artifact.is_required == true);
}

// ============================================================================
// ConfigurationValue Tests
// ============================================================================

void test_configuration_value_creation() {
    using rebuntu::setup::ConfigurationValue;
    using rebuntu::setup::ConfigurationSource;
    
    ConfigurationValue cv;
    cv.key = "core.version";
    cv.value = "1.0.0";
    cv.source = ConfigurationSource::kDefault;
    cv.is_default = true;
    
    CHECK(cv.key == "core.version");
    CHECK(cv.value == "1.0.0");
    CHECK(cv.source == ConfigurationSource::kDefault);
    CHECK(cv.is_default == true);
}

// ============================================================================
// SetupContext Tests
// ============================================================================

void test_setup_context_creation() {
    using rebuntu::setup::SetupContext;
    
    SetupContext ctx;
    ctx.scope = SetupContext::Scope::kUser;
    ctx.config_dir = "/home/user/.config/rebuntu";
    ctx.state_dir = "/home/user/.local/state/rebuntu";
    ctx.dry_run = true;
    ctx.mode = rebuntu::setup::ConfigurationMode::kStrict;
    
    CHECK(ctx.scope == SetupContext::Scope::kUser);
    CHECK(ctx.config_dir == "/home/user/.config/rebuntu");
    CHECK(ctx.state_dir == "/home/user/.local/state/rebuntu");
    CHECK(ctx.dry_run == true);
    CHECK(ctx.mode == rebuntu::setup::ConfigurationMode::kStrict);
}

// ============================================================================
// SetupResult Tests
// ============================================================================

void test_setup_result_creation() {
    using rebuntu::setup::SetupResult;
    
    SetupResult result;
    result.success = true;
    result.verified = true;
    result.phase = rebuntu::setup::SetupPhase::kComplete;
    result.is_no_op = false;
    
    CHECK(result.success == true);
    CHECK(result.verified == true);
    CHECK(result.phase == rebuntu::setup::SetupPhase::kComplete);
    CHECK(result.is_no_op == false);
}

// ============================================================================
// ConfigurationResult Tests
// ============================================================================

void test_configuration_result_creation() {
    using rebuntu::setup::ConfigurationResult;
    
    ConfigurationResult result;
    result.success = true;
    
    // Add some values
    rebuntu::setup::ConfigurationValue cv1, cv2;
    cv1.key = "core.version";
    cv1.value = "1.0.0";
    result.values.push_back(cv1);
    
    result.active_sources.push_back(rebuntu::setup::ConfigurationSource::kUserConfig);
    result.active_sources.push_back(rebuntu::setup::ConfigurationSource::kDefault);
    
    CHECK(result.success == true);
    CHECK(!result.values.empty());
    CHECK(!result.active_sources.empty());
}

// ============================================================================
// Integration Tests
// ============================================================================

void test_build_default_context() {
    using rebuntu::setup::build_default_context;
    
    auto ctx = build_default_context();
    
    // Context should be valid (either system or user scope)
    CHECK(ctx.scope == rebuntu::setup::SetupContext::Scope::kSystem ||
          ctx.scope == rebuntu::setup::SetupContext::Scope::kUser);
}

void test_setup_initial_environment_dry_run() {
    using rebuntu::setup::setup_initial_environment;
    using rebuntu::setup::SetupIntent;
    using rebuntu::setup::SetupContext;
    
    SetupIntent intent;
    intent.initial_config["core.phase"] = "1.8";
    
    SetupContext ctx;
    ctx.scope = SetupContext::Scope::kUser;
    ctx.dry_run = true;  // Don't actually create directories
    
    auto result = setup_initial_environment(intent, ctx);
    
    CHECK(result.success == true);
    CHECK(result.phase == rebuntu::setup::SetupPhase::kComplete);
}

void test_configuration_result_source_precedence() {
    using rebuntu::setup::ConfigurationResult;
    using rebuntu::setup::ConfigurationSource;
    using rebuntu::setup::apply_configuration;
    
    std::map<std::string, std::string> user_config = {
        {"custom.setting", "user_value"}
    };
    
    auto result = apply_configuration(user_config, rebuntu::setup::ConfigurationMode::kStandard);
    
    CHECK(result.success == true);
    // User config should be in active sources
    CHECK(!result.active_sources.empty());
}

// ============================================================================
// Main entry points
// ============================================================================

int main_basic_tests() {
    g_failures = 0;
    
    test_setup_phase_to_string();
    test_configuration_source_to_string();
    test_configuration_mode_to_string();
    test_setup_artifact_creation();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " basic test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_setup_basic: OK\n";
    return 0;
}

int main_value_tests() {
    g_failures = 0;
    
    test_configuration_value_creation();
    test_setup_context_creation();
    test_setup_result_creation();
    test_configuration_result_creation();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " value test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_setup_values: OK\n";
    return 0;
}

int main_integration_tests() {
    g_failures = 0;
    
    test_build_default_context();
    test_setup_initial_environment_dry_run();
    test_configuration_result_source_precedence();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " integration test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_setup_integration: OK\n";
    return 0;
}

// Full test suite entry point
int main_all() {
    int result = main_basic_tests();
    if (result != 0) return result;
    
    result = main_value_tests();
    if (result != 0) return result;
    
    result = main_integration_tests();
    return result;
}

// Standard main entry point
int main() { return main_all(); }