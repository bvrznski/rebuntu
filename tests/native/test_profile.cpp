// Unit tests for rebuntu::setup::profile (Phase 1.10)
//
// Tests Initial Profile Generation & Application:
//   * Profile = derived configuration based on user choices + constraints + capabilities
//   * Generation = produce profile from inputs and discovery
//   * Application = write profile to configuration storage

#include <portability/setup/profile.hpp>
#include <runtime/core/contracts.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

namespace {
    int g_failures = 0;
    #define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}  // namespace

// ============================================================================
// ProfileSource Tests
// ============================================================================

void test_profile_source_to_string() {
    using rebuntu::setup::profile::to_string;
    using rebuntu::setup::profile::ProfileSource;
    
    CHECK(to_string(ProfileSource::kUserInput) == "user_input");
    CHECK(to_string(ProfileSource::kPreference) == "preference");
    CHECK(to_string(ProfileSource::kDefault) == "default");
    CHECK(to_string(ProfileSource::kDiscovery) == "discovery");
    CHECK(to_string(ProfileSource::kPolicy) == "policy");
}

// ============================================================================
// ProfileStatus Tests
// ============================================================================

void test_profile_status_to_string() {
    using rebuntu::setup::profile::to_string;
    using rebuntu::setup::profile::ProfileStatus;
    
    CHECK(to_string(ProfileStatus::kPending) == "pending");
    CHECK(to_string(ProfileStatus::kGenerating) == "generating");
    CHECK(to_string(ProfileStatus::kGenerated) == "generated");
    CHECK(to_string(ProfileStatus::kApplying) == "applying");
    CHECK(to_string(ProfileStatus::kApplied) == "applied");
    CHECK(to_string(ProfileStatus::kFailed) == "failed");
    CHECK(to_string(ProfileStatus::kDegraded) == "degraded");
}

// ============================================================================
// DerivationReason Tests
// ============================================================================

void test_derivation_reason_to_string() {
    using rebuntu::setup::profile::to_string;
    using rebuntu::setup::profile::DerivationReason;
    
    CHECK(to_string(DerivationReason::kUserChoice) == "user_choice");
    CHECK(to_string(DerivationReason::kPreferenceSatisfied) == "preference_satisfied");
    CHECK(to_string(DerivationReason::kDefaultFallback) == "default_fallback");
    CHECK(to_string(DerivationReason::kDiscoveryBased) == "discovery_based");
    CHECK(to_string(DerivationReason::kPolicyEnforced) == "policy_enforced");
}

// ============================================================================
// GenerationContext Tests
// ============================================================================

void test_generation_context_creation() {
    using rebuntu::setup::profile::GenerationContext;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.config_dir = "/tmp/test_rebuntu";
    ctx.dry_run = true;
    
    CHECK(ctx.scope == GenerationContext::Scope::kUser);
    CHECK(ctx.config_dir == "/tmp/test_rebuntu");
    CHECK(ctx.dry_run == true);
}

// ============================================================================
// Profile Generation Tests
// ============================================================================

void test_profile_generation_empty_context() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    
    auto profile = generate_profile(ctx);
    
    CHECK(profile.status == rebuntu::setup::profile::ProfileStatus::kGenerated);
    // Should have some default values
    CHECK(!profile.values.empty());
}

void test_profile_generation_with_user_input() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    ctx.user_inputs["core.phase"] = "1.10";
    
    auto profile = generate_profile(ctx);
    
    CHECK(profile.status == rebuntu::setup::profile::ProfileStatus::kGenerated);
    
    // User input should be present
    auto it = profile.values.find("core.phase");
    CHECK(it != profile.values.end());
    CHECK(it->second.value == "1.10");
}

void test_profile_generation_with_discovery() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    ctx.available_options["network.interface"] = {"eth0", "wlan0"};
    
    auto profile = generate_profile(ctx);
    
    CHECK(profile.status == rebuntu::setup::profile::ProfileStatus::kGenerated);
    
    // Discovery options should be considered
    auto it = profile.values.find("network.interface");
    if (it != profile.values.end()) {
        CHECK(!it->second.value.empty());
    }
}

// ============================================================================
// Profile Validation Tests
// ============================================================================

void test_profile_validation_success() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    using rebuntu::setup::profile::validate_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    
    auto profile = generate_profile(ctx);
    auto result = validate_profile(profile);
    
    CHECK(result.is_success() || result.status == rebuntu::core::SemanticStatus::kSuccess);
}

void test_profile_diff_empty() {
    using rebuntu::setup::profile::Profile;
    using rebuntu::setup::profile::ProfileDiff;
    using rebuntu::setup::profile::diff_profile;
    
    std::map<std::string, std::string> empty_config;
    Profile profile;  // Empty profile
    
    auto diff = diff_profile(empty_config, profile);
    
    CHECK(diff.is_empty());
}

// ============================================================================
// Integration Tests
// ============================================================================

void test_profile_generate_and_diff() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    using rebuntu::setup::profile::ProfileDiff;
    using rebuntu::setup::profile::diff_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    ctx.user_inputs["core.phase"] = "1.10";
    ctx.available_options["network.interface"] = {"eth0"};
    
    auto profile = generate_profile(ctx);
    
    // Check user input was applied
    auto it = profile.values.find("core.phase");
    CHECK(it != profile.values.end());
    CHECK(it->second.value == "1.10");
    
    // Test diff with same config (should be empty)
    std::map<std::string, std::string> current_config;
    for (const auto& [k, v] : profile.values) {
        current_config[k] = v.value;
    }
    
    ProfileDiff diff = diff_profile(current_config, profile);
    CHECK(diff.is_empty());
}

void test_profile_derivation_reason() {
    using rebuntu::setup::profile::GenerationContext;
    using rebuntu::setup::profile::generate_profile;
    
    GenerationContext ctx;
    ctx.scope = GenerationContext::Scope::kUser;
    ctx.dry_run = true;
    ctx.policy_enforced.insert("security.mode");
    
    auto profile = generate_profile(ctx);
    
    // Policy-enforced key should have correct derivation reason
    for (const auto& [key, pv] : profile.values) {
        if (pv.source == rebuntu::setup::profile::ProfileSource::kPolicy) {
            CHECK(pv.reason == rebuntu::setup::profile::DerivationReason::kPolicyEnforced);
        }
    }
}

// ============================================================================
// Main entry points
// ============================================================================

int main_basic_tests() {
    g_failures = 0;
    
    test_profile_source_to_string();
    test_profile_status_to_string();
    test_derivation_reason_to_string();
    test_generation_context_creation();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " basic test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_profile_basic: OK\n";
    return 0;
}

int main_generation_tests() {
    g_failures = 0;
    
    test_profile_generation_empty_context();
    test_profile_generation_with_user_input();
    test_profile_generation_with_discovery();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " generation test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_profile_generation: OK\n";
    return 0;
}

int main_validation_tests() {
    g_failures = 0;
    
    test_profile_validation_success();
    test_profile_diff_empty();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " validation test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_profile_validation: OK\n";
    return 0;
}

int main_integration_tests() {
    g_failures = 0;
    
    test_profile_generate_and_diff();
    test_profile_derivation_reason();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " integration test check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_profile_integration: OK\n";
    return 0;
}

// Full test suite entry point
int main_all() {
    int result = main_basic_tests();
    if (result != 0) return result;
    
    result = main_generation_tests();
    if (result != 0) return result;
    
    result = main_validation_tests();
    if (result != 0) return result;
    
    result = main_integration_tests();
    return result;
}

// Standard main entry point
int main() { return main_all(); }