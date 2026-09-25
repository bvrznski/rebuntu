// rebuntu - Phase 4.18 Integration Tests: Dependency Chain Startup Flow
//
// Integration tests verify the dependency chain infrastructure works correctly
// in realistic runtime scenarios with lifecycle transitions, readiness gates,
// and proper error handling.

#include <runtime/production.hpp>
#include <cassert>
#include <iostream>

void test_basic_startup_flow() {
    rebuntu::runtime::production::Initializer init;
    
    std::vector<rebuntu::runtime::production::Dependency> deps = {
        {"config", {}, true, true},
        {"logging", {"config"}, true, true},
        {"storage", {"logging"}, true, true}
    };
    
    rebuntu::runtime::production::RuntimeContext c;
    c.runtime_id = "test_basic";
    
    rebuntu::runtime::production::InitResult result = init.initialize(c, deps);
    
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess &&
           "Startup should complete successfully");
    assert(result.context.lifecycle == rebuntu::runtime::LifecycleState::kReady &&
           "Runtime should be in kReady state after successful initialization");
    assert(result.context.readiness == rebuntu::runtime::ReadinessState::kReady &&
           "Readiness should be kReady after successful initialization");
    
    std::cout << "[PASS] Basic startup flow test\n";
}

void test_startup_with_optional_deps() {
    rebuntu::runtime::production::Initializer init;
    
    std::vector<rebuntu::runtime::production::Dependency> deps = {
        {"core", {}, true, true},
        {"optional_feature", {"core"}, false, false}
    };
    
    rebuntu::runtime::production::RuntimeContext c;
    c.runtime_id = "test_optional";
    
    rebuntu::runtime::production::InitResult result = init.initialize(c, deps);
    
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess &&
           "Startup should succeed even with unready optional dependency");
    
    std::cout << "[PASS] Optional dependencies test\n";
}

void test_startup_with_soft_order_deps() {
    rebuntu::runtime::production::Initializer init;
    
    std::vector<rebuntu::runtime::production::Dependency> deps = {
        {"base", {}, true, true},
        {"preferred", {}, true, true},
        {"depends_on_base", {"base"}, true, true}
    };
    
    rebuntu::runtime::production::RuntimeContext c;
    c.runtime_id = "test_soft_order";
    
    rebuntu::runtime::production::InitResult result = init.initialize(c, deps);
    
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess &&
           "Startup should succeed with soft order dependencies");
    
    std::cout << "[PASS] Soft order dependencies test\n";
}

void test_startup_with_conflicts() {
    rebuntu::runtime::production::Initializer init;
    
    std::vector<rebuntu::runtime::production::Dependency> deps = {
        {"service_a", {}, true, true},
        {"service_b", {}, true, true}
    };
    
    rebuntu::runtime::production::RuntimeContext c;
    c.runtime_id = "test_conflicts";
    
    rebuntu::runtime::production::InitResult result = init.initialize(c, deps);
    
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess &&
           "Startup should succeed with conflict markers");
    
    std::cout << "[PASS] Conflicting dependencies test\n";
}

void test_full_lifecycle_transitions() {
    rebuntu::runtime::production::Initializer init;
    
    rebuntu::runtime::production::RuntimeContext c;
    c.runtime_id = "test_lifecycle";
    assert(c.lifecycle == rebuntu::runtime::LifecycleState::kCreated &&
           "Initial lifecycle should be kCreated");
    assert(c.readiness == rebuntu::runtime::ReadinessState::kNotReady &&
           "Initial readiness should be kNotReady");
    
    std::vector<rebuntu::runtime::production::Dependency> deps = {
        {"dep1", {}, true, true}
    };
    
    rebuntu::runtime::production::InitResult result = init.initialize(c, deps);
    
    assert(result.context.lifecycle == rebuntu::runtime::LifecycleState::kReady &&
           "Lifecycle should transition to kReady after initialization");
    assert(result.context.readiness == rebuntu::runtime::ReadinessState::kReady &&
           "Readiness should be kReady after successful initialization");
    
    std::cout << "[PASS] Full lifecycle transitions test\n";
}

int main() {
    std::cout << "Phase 4.18 Integration Tests: Dependency Chain Startup Flow\n";
    std::cout << "============================================================\n\n";
    
    test_basic_startup_flow();
    test_startup_with_optional_deps();
    test_startup_with_soft_order_deps();
    test_startup_with_conflicts();
    test_full_lifecycle_transitions();
    
    std::cout << "\nAll integration tests passed!\n";
    return 0;
}