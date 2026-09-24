// Unit tests for rebuntu::install::planning (Phase 1.2)
//
// Tests installation planning functionality.

#include <system/install/contracts.hpp>
#include <system/install/planning.hpp>

#include <iostream>
#include <cassert>

using namespace rebuntu::install;
using namespace rebuntu::install::planning;

void test_planner_construction() {
    Planner planner;
    std::cout << "test_planner_construction: OK\n";
}

void test_installation_intent_creation() {
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = InstallationScope::kSystem;
    intent.skip_verification = false;
    
    assert(intent.version == "1.0.0");
    assert(intent.scope == InstallationScope::kSystem);
    assert(!intent.skip_verification);
    
    std::cout << "test_installation_intent_creation: OK\n";
}

void test_installation_plan_creation() {
    InstallationIntent intent;
    intent.version = "1.0.0";
    intent.scope = InstallationScope::kSystem;
    
    Planner planner;
    auto plan = planner.produce_plan(intent);
    
    assert(plan.version == "1.0.0");
    assert(plan.scope == InstallationScope::kSystem);
    assert(plan.is_dry_run == true);
    assert(!plan.steps.empty());
    
    std::cout << "test_installation_plan_creation: OK\n";
}

void test_preflight_evaluator() {
    PreflightEvaluator evaluator;
    auto results = evaluator.evaluate();
    
    assert(!results.empty());
    
    std::cout << "test_preflight_evaluator: OK (got " << results.size() << " checks)\n";
}

void test_has_blockers() {
    Planner planner;
    
    // Test with no blockers
    std::vector<PreInstallationCheckResult> checks;
    PreInstallationCheckResult check1;
    check1.level = PreInstallationCheckResult::Level::kInfo;
    check1.passed = true;
    checks.push_back(check1);
    
    assert(!planner.has_blockers(checks));
    
    // Test with a blocker
    PreInstallationCheckResult check2;
    check2.level = PreInstallationCheckResult::Level::kBlocker;
    check2.passed = false;
    checks.push_back(check2);
    
    assert(planner.has_blockers(checks));
    
    std::cout << "test_has_blockers: OK\n";
}

int main() {
    std::cout << "=== Installation Planning Tests (Phase 1.2) ===\n\n";
    
    test_planner_construction();
    test_installation_intent_creation();
    test_preflight_evaluator();
    test_installation_plan_creation();
    test_has_blockers();
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}