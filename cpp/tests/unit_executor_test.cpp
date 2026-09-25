// rebuntu::runtime::unit_executor tests - Phase 4.11 Unit Execution Runtime

#include <runtime/unit_executor.hpp>
#include <cassert>
#include <iostream>

void test_unit_executor_creation() {
    auto executor = rebuntu::runtime::unit_executor::make_unit_executor();
    assert(executor != nullptr);
}

void test_unit_executor_metrics_initial() {
    auto executor = rebuntu::runtime::unit_executor::make_unit_executor();
    auto metrics = executor->metrics();
    assert(metrics.executions_submitted == 0);
    assert(metrics.executions_completed == 0);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 4.11 Unit Executor tests...\n";
    
    test_unit_executor_creation();
    std::cout << "  test_unit_executor_creation... PASS\n";
    
    test_unit_executor_metrics_initial();
    std::cout << "  test_unit_executor_metrics_initial... PASS\n";
    
    std::cout << "All unit executor tests PASSED!\n";
    return 0;
}