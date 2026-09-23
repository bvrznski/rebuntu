/// Unit tests for rebuntu::install::planning (Phase 1.2)
///
/// Tests installation planning and environment preparation logic.

#include <system/install/planning.hpp>

#include <iostream>
#include <string>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

// ============================================================================
// Helper Types
// ============================================================================

using rebuntu::install::planning::InstallationIntent;
using rebuntu::install::planning::InstallationPlan;
using rebuntu::install::planning::InstallationStep;
using rebuntu::install::planning::DependencyInfo;
using rebuntu::install::planning::PreInstallationCheckResult;
using rebuntu::install::planning::Planner;
using rebuntu::install::planning::PreflightEvaluator;

using rebuntu::environment::discovery::DiscoveryStatus;
using rebuntu::environment::discovery::HostDiscoveryResult;
using rebuntu::environment::discovery::CpuArchitecture;

// ============================================================================
// Test Fixture: create a minimal host discovery result for testing
// ============================================================================

static HostDiscoveryResult make_test_host() {
    HostDiscoveryResult result;
    result.distribution.id = "ubuntu";
    result.distribution.version = "22.04";
    result.distribution.status = DiscoveryStatus::kKnown;
    
    result.architecture.cpu = CpuArchitecture::kX86_64;
    result.architecture.status = DiscoveryStatus::kKnown;
    
    result.privilege.is_root = true;
    result.privilege.elevation = rebuntu::environment::discovery::ElevationCapability::kAlreadyElevated;
    result.privilege.status = DiscoveryStatus::kKnown;
    
    result.filesystem.home_dir = "/home/testuser";
    result.filesystem.xdg_config_home = "/home/testuser/.config";
    result.filesystem.xdg_data_home = "/home/testuser/.local/share";
    result.filesystem.system_bin_path = "/usr/bin";
    result.filesystem.user_bin_path = "/home/testuser/.local/bin";
    result.filesystem.status = DiscoveryStatus::kKnown;
    
    result.package_manager.available.push_back(rebuntu::environment::discovery::PackageManager::kApt);
    result.package_manager.available.push_back(rebuntu::environment::discovery::PackageManager::kDpkg);
    result.package_manager.status = DiscoveryStatus::kKnown;
    
    return result;
}

// ============================================================================
// Basic Tests (Phase 1.2)
// ============================================================================

void test_planner_construction() {
    auto host = make_test_host();
    Planner planner(host);
}

void test_system_scope_installation() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.status == InstallationPlan::Status::kReady ||
          plan.status == InstallationPlan::Status::kWarningOnly);
    CHECK(plan.version == "1.0.0");
    CHECK(plan.scope == rebuntu::install::InstallationScope::kSystem);
    CHECK(plan.is_dry_run == true);
    CHECK(!plan.steps.empty());
}

void test_user_scope_installation() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kUser;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.version == "1.0.0");
    CHECK(plan.scope == rebuntu::install::InstallationScope::kUser);
    CHECK(!plan.steps.empty());
}

void test_preflight_checks_populated() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(!plan.preflight_checks.empty());
}

void test_dependencies_resolved() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(!plan.dependencies.empty());
}

void test_installation_step_types() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    for (const auto& step : plan.steps) {
        bool valid_type = (step.type == InstallationStep::Type::kValidate ||
                          step.type == InstallationStep::Type::kCreateDirectory ||
                          step.type == InstallationStep::Type::kCopyFile ||
                          step.type == InstallationStep::Type::kSetPermissions ||
                          step.type == InstallationStep::Type::kVerify);
        CHECK(valid_type);
    }
}

void test_expected_postconditions() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(!plan.expected_postconditions.empty());
}

void test_verification_steps_exist() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    bool has_verify_steps = false;
    for (const auto& step : plan.steps) {
        if (!step.verification_steps.empty()) {
            has_verify_steps = true;
            break;
        }
    }
    CHECK(has_verify_steps);
}

void test_rollback_strategy() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.rollback_description.has_value());
}

void test_preflight_evaluator() {
    auto host = make_test_host();
    
    PreflightEvaluator evaluator(host);
    auto results = evaluator.evaluate();
    
    CHECK(!results.empty());
    
    for (const auto& result : results) {
        CHECK(!result.name.empty());
        bool valid_level = (result.level == PreInstallationCheckResult::Level::kInfo ||
                           result.level == PreInstallationCheckResult::Level::kWarning ||
                           result.level == PreInstallationCheckResult::Level::kBlocker);
        CHECK(valid_level);
    }
}

// ============================================================================
// Idempotency Tests (Phase 1.2)
// ============================================================================

void test_idempotent_plans() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan1 = planner.produce_plan(intent);
    InstallationPlan plan2 = planner.produce_plan(intent);
    
    CHECK(plan1.status == plan2.status);
    CHECK(plan1.steps.size() == plan2.steps.size());
    CHECK(plan1.preflight_checks.size() == plan2.preflight_checks.size());
}

// ============================================================================
// Failure-path Tests (Phase 1.2)  
// ============================================================================

void test_blocker_when_system_without_root() {
    HostDiscoveryResult host;
    host.distribution.id = "ubuntu";
    host.distribution.version = "22.04";
    host.distribution.status = DiscoveryStatus::kKnown;
    
    host.architecture.cpu = CpuArchitecture::kX86_64;
    host.architecture.status = DiscoveryStatus::kKnown;
    
    host.privilege.is_root = false;
    host.privilege.elevation = rebuntu::environment::discovery::ElevationCapability::kNone;
    host.privilege.status = DiscoveryStatus::kKnown;
    
    host.filesystem.home_dir = "/home/testuser";
    host.filesystem.xdg_config_home = "/home/testuser/.config";
    host.filesystem.xdg_data_home = "/home/testuser/.local/share";
    host.filesystem.system_bin_path = "/usr/bin";
    host.filesystem.user_bin_path = "/home/testuser/.local/bin";
    host.filesystem.status = DiscoveryStatus::kKnown;
    
    host.package_manager.available.push_back(rebuntu::environment::discovery::PackageManager::kApt);
    host.package_manager.status = DiscoveryStatus::kKnown;
    
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.status == InstallationPlan::Status::kBlocked ||
          plan.preflight_checks.size() > 0);
}

void test_user_scope_without_home() {
    HostDiscoveryResult host;
    host.distribution.id = "ubuntu";
    host.distribution.version = "22.04";
    host.distribution.status = DiscoveryStatus::kKnown;
    
    host.architecture.cpu = CpuArchitecture::kX86_64;
    host.architecture.status = DiscoveryStatus::kKnown;
    
    host.privilege.is_root = false;
    host.privilege.elevation = rebuntu::environment::discovery::ElevationCapability::kNone;
    host.privilege.status = DiscoveryStatus::kKnown;
    
    host.filesystem.home_dir = std::nullopt;
    host.filesystem.xdg_config_home = "/home/testuser/.config";
    host.filesystem.xdg_data_home = "/home/testuser/.local/share";
    host.filesystem.system_bin_path = "/usr/bin";
    host.filesystem.user_bin_path = "/home/testuser/.local/bin";
    host.filesystem.status = DiscoveryStatus::kKnown;
    
    host.package_manager.available.push_back(rebuntu::environment::discovery::PackageManager::kApt);
    host.package_manager.status = DiscoveryStatus::kKnown;
    
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kUser;
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.preflight_checks.size() > 0 ||
          plan.status == InstallationPlan::Status::kBlocked);
}

void test_optional_features_dependency_resolution() {
    auto host = make_test_host();
    Planner planner(host);
    
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = rebuntu::install::InstallationScope::kSystem;
    intent.optional_features.push_back("semantic");
    
    InstallationPlan plan = planner.produce_plan(intent);
    
    CHECK(plan.dependencies.size() > 0);
}

// ============================================================================
// Main entry points
// ============================================================================

int main_basic_tests() {
    g_failures = 0;
    
    test_planner_construction();
    test_system_scope_installation();
    test_user_scope_installation();
    test_preflight_checks_populated();
    test_dependencies_resolved();
    test_installation_step_types();
    test_expected_postconditions();
    test_verification_steps_exist();
    test_rollback_strategy();
    test_preflight_evaluator();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " basic test check(s) FAILED\\n";
        return 1;
    }
    std::cout << "test_install_planning_basic: OK\\n";
    return 0;
}

int main_idempotency_and_failures() {
    g_failures = 0;
    
    test_idempotent_plans();
    test_blocker_when_system_without_root();
    test_user_scope_without_home();
    test_optional_features_dependency_resolution();
    
    if (g_failures != 0) {
        std::cerr << g_failures << " failure-path/idempotency check(s) FAILED\\n";
        return 1;
    }
    std::cout << "test_install_planning_failure: OK\\n";
    return 0;
}

// Full test suite entry point
int main_all() {
    int result = main_basic_tests();
    if (result != 0) return result;
    
    result = main_idempotency_and_failures();
    return result;
}

// Standard main entry point
int main() { return main_all(); }
