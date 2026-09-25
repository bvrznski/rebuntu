// rebuntu::runtime::production - Integration Tests (Phase 4.1)
//
// Test Phase 4.1 Core Initialization implementation in production runtime.

#include <runtime/production.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::runtime::production;

void test_initializer_with_no_dependencies() {
    Initializer init;
    RuntimeContext ctx;
    std::vector<Dependency> deps = {};
    
    auto result = init.initialize(ctx, deps);
    
    assert(result.outcome.status == core::SemanticStatus::kSuccess);
    assert(result.failed_stage.has_value() == false);
    assert(result.context.lifecycle == LifecycleState::kReady);
    assert(result.context.readiness == ReadinessState::kReady);
}

void test_initializer_with_linear_dependencies() {
    Initializer init;
    
    Dependency dep_a = {"a", {}, true, true};
    Dependency dep_b = {"b", {"a"}, true, true};
    Dependency dep_c = {"c", {"b"}, true, true};
    std::vector<Dependency> deps = {dep_a, dep_b, dep_c};
    
    auto result = init.initialize(RuntimeContext{}, deps);
    
    assert(result.outcome.status == core::SemanticStatus::kSuccess);
}

void test_initializer_with_dependency_cycle() {
    Initializer init;
    
    // Create a cycle: a -> b -> c -> a
    Dependency dep_a = {"a", {"c"}, true, true};
    Dependency dep_b = {"b", {"a"}, true, true};
    Dependency dep_c = {"c", {"b"}, true, true};
    std::vector<Dependency> deps = {dep_a, dep_b, dep_c};
    
    auto result = init.initialize(RuntimeContext{}, deps);
    
    // Should detect the cycle and fail
    assert(result.outcome.status == core::SemanticStatus::kFailure);
    assert(result.failed_stage.has_value() && *result.failed_stage == "dependencies");
}

void test_initializer_with_unready_dependency() {
    Initializer init;
    
    Dependency dep_a = {"a", {}, true, false};  // Not ready
    Dependency dep_b = {"b", {"a"}, true, true};
    std::vector<Dependency> deps = {dep_a, dep_b};
    
    auto result = init.initialize(RuntimeContext{}, deps);
    
    assert(result.outcome.status == core::SemanticStatus::kFailure);
}

void test_startup_order_linear() {
    Dependency dep_a = {"a", {}, true, true};
    Dependency dep_b = {"b", {"a"}, true, true};
    Dependency dep_c = {"c", {"b"}, true, true};
    std::vector<Dependency> deps = {dep_a, dep_b, dep_c};
    
    auto order = Initializer::startup_order(deps);
    
    assert(order.has_value());
    assert(order->size() == 3);
    // Order should be: a before b, b before c
    assert(order->at(0) == "a");
    assert(order->at(1) == "b");
    assert(order->at(2) == "c");
}

void test_startup_order_with_multiple_roots() {
    Dependency dep_a = {"a", {}, true, true};
    Dependency dep_b = {"b", {}, true, true};
    Dependency dep_c = {"c", {"a"}, true, true};
    std::vector<Dependency> deps = {dep_a, dep_b, dep_c};
    
    auto order = Initializer::startup_order(deps);
    
    assert(order.has_value());
    assert(order->size() == 3);
    // a should come before c
    assert(std::find(order->begin(), order->end(), "a") < std::find(order->begin(), order->end(), "c"));
}

void test_startup_order_detects_cycle() {
    Dependency dep_a = {"a", {"b"}, true, true};
    Dependency dep_b = {"b", {"a"}, true, true};  // Creates cycle: a -> b -> a
    std::vector<Dependency> deps = {dep_a, dep_b};
    
    auto order = Initializer::startup_order(deps);
    
    // Should return nullopt for cyclic dependencies
    assert(!order.has_value());
}

int main() {
    std::cout << "Running Phase 4.1 Initialization Tests..." << std::endl;
    
    test_initializer_with_no_dependencies();
    std::cout << "  [PASS] test_initializer_with_no_dependencies" << std::endl;
    
    test_initializer_with_linear_dependencies();
    std::cout << "  [PASS] test_initializer_with_linear_dependencies" << std::endl;
    
    test_initializer_with_dependency_cycle();
    std::cout << "  [PASS] test_initializer_with_dependency_cycle" << std::endl;
    
    test_initializer_with_unready_dependency();
    std::cout << "  [PASS] test_initializer_with_unready_dependency" << std::endl;
    
    test_startup_order_linear();
    std::cout << "  [PASS] test_startup_order_linear" << std::endl;
    
    test_startup_order_with_multiple_roots();
    std::cout << "  [PASS] test_startup_order_with_multiple_roots" << std::endl;
    
    test_startup_order_detects_cycle();
    std::cout << "  [PASS] test_startup_order_detects_cycle" << std::endl;
    
    std::cout << "\nAll Phase 4.1 initialization tests passed!" << std::endl;
    return 0;
}