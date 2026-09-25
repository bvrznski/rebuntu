// rebuntu::runtime::workflow — Tests (Phase 4.14)
//
// Tests for Phase 4.14 Workflow Runtime:
//   - WorkflowDefinition to WorkflowExecution transformation
//   - DAG-based step ordering via topological sort
//   - Sequential execution with dependency tracking
//   - Cancellation propagation
//   - Error handling and validation

#include <runtime/workflow.hpp>
#include <runtime/contracts.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/core/contracts.hpp>
#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

using namespace rebuntu::runtime;
using namespace rebuntu::core;

// ============================================================================
// WorkflowValidator Tests
// ============================================================================

void test_validator_no_cycle() {
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}},
        {"step_c", work::ExecutionMode::kInline, {}, {"step_b"}, {}}
    };
    
    WorkflowValidator validator;
    bool has_cycle = validator.has_cycle(nodes);
    
    assert(!has_cycle && "Linear dependencies should not have cycles");
    std::cout << "test_validator_no_cycle: PASSED" << std::endl;
}

void test_validator_has_cycle() {
    // A -> B -> C -> A (cycle)
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {"step_c"}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}},
        {"step_c", work::ExecutionMode::kInline, {}, {"step_b"}, {}}
    };
    
    WorkflowValidator validator;
    bool has_cycle = validator.has_cycle(nodes);
    
    assert(has_cycle && "Circular dependencies should be detected");
    std::cout << "test_validator_has_cycle: PASSED" << std::endl;
}

void test_validator_dependencies_ok() {
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}}
    };
    
    WorkflowValidator validator;
    auto errors = validator.validate_dependencies(nodes);
    
    assert(errors.empty() && "Valid dependencies should have no errors");
    std::cout << "test_validator_dependencies_ok: PASSED" << std::endl;
}

void test_validator_unknown_dependency() {
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"unknown_step"}, {}}
    };
    
    WorkflowValidator validator;
    auto errors = validator.validate_dependencies(nodes);
    
    assert(!errors.empty() && "Unknown dependency should generate error");
    std::cout << "test_validator_unknown_dependency: PASSED" << std::endl;
}

void test_validator_topological_sort() {
    // B -> A (B depends on A, so order should be A, B)
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}}
    };
    
    WorkflowValidator validator;
    auto order_opt = validator.compute_execution_order(nodes);
    
    assert(order_opt.has_value() && "Valid DAG should produce execution order");
    const auto& order = *order_opt;
    
    // A must come before B
    size_t a_pos = std::find(order.begin(), order.end(), "step_a") - order.begin();
    size_t b_pos = std::find(order.begin(), order.end(), "step_b") - order.begin();
    
    assert(a_pos < b_pos && "Dependencies should be executed in correct order");
    std::cout << "test_validator_topological_sort: PASSED" << std::endl;
}

// ============================================================================
// WorkflowExecutor Tests
// ============================================================================

void test_executor_basic_success() {
    auto handler = [](const WorkflowNode& node, CancellationToken& token) -> rebuntu::core::Outcome {
        (void)node;
        if (token.is_cancelled()) {
            return rebuntu::core::Outcome{
                .status = rebuntu::core::SemanticStatus::kCancelled,
                .evidence = {}
            };
        }
        return rebuntu::core::Outcome{
            .status = rebuntu::core::SemanticStatus::kSuccess,
            .evidence = {}
        };
    };
    
    WorkflowExecutor executor(handler);
    
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}}
    };
    
    WorkflowDefinition def{"test_workflow"};
    def.title = "Test Workflow";
    def.description = "A simple test workflow";
    def.nodes = nodes;
    
    CancellationToken cancel_token;
    WorkflowRun run = executor.execute(def, cancel_token);
    
    assert(run.state == WorkflowRunState::kSucceeded && "Workflow should succeed");
    std::cout << "test_executor_basic_success: PASSED" << std::endl;
}

void test_executor_multiple_steps() {
    auto handler = [](const WorkflowNode& node, CancellationToken& token) -> rebuntu::core::Outcome {
        (void)token;
        return rebuntu::core::Outcome{
            .status = rebuntu::core::SemanticStatus::kSuccess,
            .evidence = {}
        };
    };
    
    WorkflowExecutor executor(handler);
    
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}},
        {"step_c", work::ExecutionMode::kInline, {}, {"step_b"}, {}}
    };
    
    WorkflowDefinition def{"test_workflow"};
    def.nodes = nodes;
    
    CancellationToken cancel_token;
    WorkflowRun run = executor.execute(def, cancel_token);
    
    assert(run.state == WorkflowRunState::kSucceeded && "Workflow should succeed");
    assert(run.step_results.size() == 3 && "All steps should execute");
    std::cout << "test_executor_multiple_steps: PASSED" << std::endl;
}

void test_executor_cancellation() {
    auto handler = [](const WorkflowNode& node, CancellationToken& token) -> rebuntu::core::Outcome {
        if (token.is_cancelled()) {
            return rebuntu::core::Outcome{
                .status = rebuntu::core::SemanticStatus::kCancelled,
                .evidence = {}
            };
        }
        // Simulate some work before allowing cancellation
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return rebuntu::core::Outcome{
            .status = rebuntu::core::SemanticStatus::kSuccess,
            .evidence = {}
        };
    };
    
    WorkflowExecutor executor(handler);
    
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}}
    };
    
    WorkflowDefinition def{"test_workflow"};
    def.nodes = nodes;
    
    CancellationToken cancel_token;
    // Cancel immediately
    cancel_token.request_cancel();
    
    WorkflowRun run = executor.execute(def, cancel_token);
    
    assert(run.state == WorkflowRunState::kCancelled && "Workflow should be cancelled");
    std::cout << "test_executor_cancellation: PASSED" << std::endl;
}

void test_executor_failure_propagation() {
    bool first_step_called = false;
    auto handler = [&first_step_called](const WorkflowNode& node, CancellationToken& token) -> rebuntu::core::Outcome {
        (void)token;
        
        if (node.id == "step_a") {
            first_step_called = true;
            // First step succeeds
            return rebuntu::core::Outcome{
                .status = rebuntu::core::SemanticStatus::kSuccess,
                .evidence = {}
            };
        } else if (node.id == "step_b") {
            // Second step fails
            return rebuntu::core::Outcome{
                .status = rebuntu::core::SemanticStatus::kFailure,
                .error = Error{"E_STEP_EXECUTION_FAILED", "step failed"}
            };
        }
        
        return rebuntu::core::Outcome{
            .status = rebuntu::core::SemanticStatus::kUnknown,
            .evidence = {}
        };
    };
    
    WorkflowExecutor executor(handler);
    
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}},
        {"step_b", work::ExecutionMode::kInline, {}, {"step_a"}, {}}
    };
    
    WorkflowDefinition def{"test_workflow"};
    def.nodes = nodes;
    
    CancellationToken cancel_token;
    WorkflowRun run = executor.execute(def, cancel_token);
    
    assert(run.state == WorkflowRunState::kFailed && "Workflow should fail");
    assert(first_step_called && "First step should have executed");
    std::cout << "test_executor_failure_propagation: PASSED" << std::endl;
}

void test_workflow_run_timing() {
    auto handler = [](const WorkflowNode& node, CancellationToken& token) -> rebuntu::core::Outcome {
        (void)node;
        (void)token;
        return rebuntu::core::Outcome{
            .status = rebuntu::core::SemanticStatus::kSuccess,
            .evidence = {}
        };
    };
    
    WorkflowExecutor executor(handler);
    
    std::vector<WorkflowNode> nodes = {
        {"step_a", work::ExecutionMode::kInline, {}, {}}
    };
    
    WorkflowDefinition def{"test_workflow"};
    def.nodes = nodes;
    
    CancellationToken cancel_token;
    auto start = std::chrono::system_clock::now();
    WorkflowRun run = executor.execute(def, cancel_token);
    auto end = std::chrono::system_clock::now();
    
    assert(run.started_at >= start && "Started at should be after request start");
    assert(run.completed_at <= end && "Completed at should be before now");
    std::cout << "test_workflow_run_timing: PASSED" << std::endl;
}

// ============================================================================
// Main test suite
// ============================================================================

int main() {
    std::cout << "=== Phase 4.14 Workflow Runtime Tests ===" << std::endl;
    
    // Validator tests
    std::cout << "\n--- WorkflowValidator Tests ---" << std::endl;
    test_validator_no_cycle();
    test_validator_has_cycle();
    test_validator_dependencies_ok();
    test_validator_unknown_dependency();
    test_validator_topological_sort();
    
    // Executor tests
    std::cout << "\n--- WorkflowExecutor Tests ---" << std::endl;
    test_executor_basic_success();
    test_executor_multiple_steps();
    test_executor_cancellation();
    test_executor_failure_propagation();
    test_workflow_run_timing();
    
    std::cout << "\n=== All Phase 4.14 workflow tests passed! ===" << std::endl;
    return 0;
}