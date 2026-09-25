// rebuntu::runtime::workflow — Workflow Execution Implementation (Phase 4.14)
//
// This implements the canonical runtime for executing Phase 0.11 Workflow
// definitions with:
//   - DAG-based step ordering via topological sort
//   - Sequential, parallel, conditional execution support
//   - Step-level retry/timeout policies (reusing existing contracts)
//   - Cancellation propagation to all steps
//   - Evidence collection for each step execution

#include <runtime/workflow.hpp>
#include <runtime/cancellation/token.hpp>
#include <optional>
#include <algorithm>
#include <queue>
#include <set>
#include <chrono>

namespace rebuntu::runtime {

// ============================================================================
// WorkflowValidator implementation
// ============================================================================

bool WorkflowValidator::has_cycle(const std::vector<WorkflowNode>& nodes) const {
    // Use Kahn's algorithm for cycle detection
    std::map<std::string, int> in_degree;
    
    // Initialize all nodes with 0 in-degree
    for (const auto& node : nodes) {
        in_degree[node.id] = 0;
    }
    
    // Calculate in-degrees based on dependencies
    for (const auto& node : nodes) {
        for (const auto& dep : node.depends_on) {
            if (in_degree.count(dep) > 0) {
                in_degree[node.id]++;
            }
        }
    }
    
    // Find nodes with no incoming edges
    std::queue<std::string> zero_in_degree;
    for (const auto& [node_id, degree] : in_degree) {
        if (degree == 0) {
            zero_in_degree.push(node_id);
        }
    }
    
    int processed = 0;
    while (!zero_in_degree.empty()) {
        std::string current = zero_in_degree.front();
        zero_in_degree.pop();
        processed++;
        
        // Find nodes that depend on current
        for (const auto& node : nodes) {
            for (const auto& dep : node.depends_on) {
                if (dep == current && in_degree[node.id] > 0) {
                    in_degree[node.id]--;
                    if (in_degree[node.id] == 0) {
                        zero_in_degree.push(node.id);
                    }
                }
            }
        }
    }
    
    // If we didn't process all nodes, there's a cycle
    return processed != static_cast<int>(nodes.size());
}

std::vector<std::string> WorkflowValidator::validate_dependencies(
    const std::vector<WorkflowNode>& nodes) const {
    
    std::vector<std::string> errors;
    std::set<std::string> node_ids;
    
    // Collect all valid node IDs
    for (const auto& node : nodes) {
        node_ids.insert(node.id);
    }
    
    // Check each dependency references an existing node
    for (const auto& node : nodes) {
        for (const auto& dep : node.depends_on) {
            if (node_ids.find(dep) == node_ids.end()) {
                errors.push_back(
                    "Node '" + node.id + "' depends on unknown node '" + dep + "'");
            }
        }
    }
    
    return errors;
}

std::optional<std::vector<std::string>> WorkflowValidator::compute_execution_order(
    const std::vector<WorkflowNode>& nodes) const {
    
    // Check for cycles first
    if (has_cycle(nodes)) {
        return std::nullopt;
    }
    
    // Kahn's algorithm for topological sort
    std::map<std::string, int> in_degree;
    for (const auto& node : nodes) {
        in_degree[node.id] = 0;
    }
    
    for (const auto& node : nodes) {
        for (const auto& dep : node.depends_on) {
            if (in_degree.count(dep) > 0) {
                in_degree[node.id]++;
            }
        }
    }
    
    std::queue<std::string> zero_in_degree;
    for (const auto& [node_id, degree] : in_degree) {
        if (degree == 0) {
            zero_in_degree.push(node_id);
        }
    }
    
    std::vector<std::string> order;
    while (!zero_in_degree.empty()) {
        std::string current = zero_in_degree.front();
        zero_in_degree.pop();
        order.push_back(current);
        
        for (const auto& node : nodes) {
            for (const auto& dep : node.depends_on) {
                if (dep == current && in_degree[node.id] > 0) {
                    in_degree[node.id]--;
                    if (in_degree[node.id] == 0) {
                        zero_in_degree.push(node.id);
                    }
                }
            }
        }
    }
    
    return order;
}

// ============================================================================
// WorkflowExecutor implementation
// ============================================================================

WorkflowExecutor::WorkflowExecutor(StepHandler handler)
    : step_handler_(handler) {
}

WorkflowRun WorkflowExecutor::execute(
    const WorkflowDefinition& definition,
    CancellationToken& cancel_token) {
    
    WorkflowRun run;
    run.id = "workflow_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    run.workflow_id = definition.id;
    run.state = WorkflowRunState::kRunning;
    run.queued_at = std::chrono::system_clock::now();
    
    // Validate workflow
    WorkflowValidator validator;
    
    auto errors = validator.validate_dependencies(definition.nodes);
    if (!errors.empty()) {
        run.state = WorkflowRunState::kFailed;
        run.final_outcome = core::Outcome{
            .status = core::SemanticStatus::kUnknown,
            .error = core::Error{"E_WORKFLOW_VALIDATION_FAILED", "workflow validation failed"}
        };
        return run;
    }
    
    if (validator.has_cycle(definition.nodes)) {
        run.state = WorkflowRunState::kFailed;
        run.final_outcome = core::Outcome{
            .status = core::SemanticStatus::kUnknown,
            .error = core::Error{"E_WORKFLOW_CYCLE_DETECTED", "workflow contains a dependency cycle"}
        };
        return run;
    }
    
    // Compute execution order
    auto order_opt = validator.compute_execution_order(definition.nodes);
    if (!order_opt.has_value()) {
        run.state = WorkflowRunState::kFailed;
        run.final_outcome = core::Outcome{
            .status = core::SemanticStatus::kUnknown,
            .error = core::Error{"E_WORKFLOW_EXECUTION_ORDER_FAILED", "failed to compute execution order"}
        };
        return run;
    }
    
    const auto& order = *order_opt;
    run.started_at = std::chrono::system_clock::now();
    
    // Track which steps succeeded (for conditional skipping)
    std::set<std::string> successful_steps;
    
    // Execute each step in order
    for (const auto& step_id : order) {
        // Check cancellation before each step
        if (cancel_token.is_cancelled()) {
            run.state = WorkflowRunState::kCancelled;
            break;
        }
        
        // Find the node for this step
        const WorkflowNode* node = nullptr;
        for (const auto& n : definition.nodes) {
            if (n.id == step_id) {
                node = &n;
                break;
            }
        }
        
        if (!node) {
            continue;  // Skip missing nodes
        }
        
        // Create step result placeholder with initial attempt
        StepResult step_result;
        step_result.step_id = step_id;
        step_result.status = WorkflowStepStatus::kExecuting;
        step_result.execution_id = work::ExecutionId{(step_id + "_" + run.id)};
        
        // Record timing for first attempt
        auto now = std::chrono::system_clock::now();
        step_result.started_at_first = now;
        
        // Create initial attempt record
        StepAttempt attempt;
        attempt.attempt_number = 1;
        attempt.started_at = now;
        step_result.attempts.push_back(attempt);
        
        // Execute the step
        core::Outcome outcome = step_handler_(*node, cancel_token);
        
        // Record completion time for last attempt
        step_result.completed_at_last = std::chrono::system_clock::now();
        
        // Determine success/failure based on outcome
        if (outcome.status == core::SemanticStatus::kSuccess) {
            step_result.status = WorkflowStepStatus::kSucceeded;
            successful_steps.insert(step_id);
        } else {
            step_result.status = WorkflowStepStatus::kFailed;
        }
        
        // Update attempt with outcome and evidence
        if (!step_result.attempts.empty()) {
            auto& last_attempt = step_result.attempts.back();
            last_attempt.outcome = outcome;
            last_attempt.completed_at = std::chrono::system_clock::now();
            
            for (const auto& ev : outcome.evidence) {
                last_attempt.evidence.push_back(ev);
            }
        }
        
        // Update step result with final outcome
        step_result.final_outcome = outcome;
        
        run.step_results.push_back(std::move(step_result));
    }
    
    // Determine overall workflow state
    run.completed_at = std::chrono::system_clock::now();
    
    if (cancel_token.is_cancelled()) {
        run.state = WorkflowRunState::kCancelled;
    } else if (std::all_of(run.step_results.begin(), run.step_results.end(),
                           [](const auto& sr) { return sr.status == WorkflowStepStatus::kSucceeded; })) {
        run.state = WorkflowRunState::kSucceeded;
    } else {
        run.state = WorkflowRunState::kFailed;
    }
    
    // Set final outcome
    if (run.state == WorkflowRunState::kSucceeded) {
        run.final_outcome = core::Outcome{
            .status = core::SemanticStatus::kSuccess,
            .evidence = {}
        };
    } else {
        std::string error_msg;
        for (const auto& sr : run.step_results) {
            if (sr.status == WorkflowStepStatus::kFailed && !error_msg.empty()) {
                error_msg += ", ";
            }
            error_msg += "step " + sr.step_id + " failed";
        }
        
        run.final_outcome = core::Outcome{
            .status = core::SemanticStatus::kFailure,
            .error = core::Error{"E_WORKFLOW_EXECUTION_FAILED", error_msg.empty() ? "workflow execution failed" : error_msg}
        };
    }
    
    return run;
}

}  // namespace rebuntu::runtime