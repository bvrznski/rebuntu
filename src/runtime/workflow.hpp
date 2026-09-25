// rebuntu::runtime::workflow — Workflow execution semantics (Phase 4.12)
//
// This header establishes Rebuntu's workflow execution model:
//   - Workflow = ordered graph of steps with dependency constraints
//   - StepResult = outcome of one step with evidence and retry attempts
//   - WorkflowRun = complete execution of a workflow with final state
//
// Key semantics established here:
//   * Workflow != Task (Tasks are parameterized Operations, Workflows are step sequences)
//   * Workflow steps may themselves execute Tasks/Operations
//   * Workflows preserve attempt history across retries

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/contracts.hpp>
#include <runtime/work.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime {

// ---------------------------------------------------------------------------
// WorkflowStepStatus — Status of one workflow step
// ---------------------------------------------------------------------------
enum class WorkflowStepStatus {
    kPending,       // not yet executed
    kExecuting,     // currently running
    kSucceeded,     // completed successfully
    kFailed,        // failed (may retry)
    kSkipped,       // skipped due to dependency failure
};

inline std::string_view to_string(WorkflowStepStatus s) {
    switch (s) {
        case WorkflowStepStatus::kPending:   return "pending";
        case WorkflowStepStatus::kExecuting: return "executing";
        case WorkflowStepStatus::kSucceeded: return "succeeded";
        case WorkflowStepStatus::kFailed:    return "failed";
        case WorkflowStepStatus::kSkipped:   return "skipped";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// StepResult — Result of executing one workflow step
// ---------------------------------------------------------------------------
struct StepResult {
    std::string step_id;
    
    WorkflowStepStatus status = WorkflowStepStatus::kPending;
    
    // Execution details
    work::ExecutionId execution_id;
    int attempt_number = 0;
    
    // Timing
    std::chrono::system_clock::time_point started_at{};
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Outcome
    core::Outcome outcome;
    
    // Evidence collected during step execution
    std::vector<core::Evidence> evidence;
};

// ---------------------------------------------------------------------------
// WorkflowRunState — Overall state of a workflow execution
// ---------------------------------------------------------------------------
enum class WorkflowRunState {
    kQueued,        // waiting for resources
    kRunning,       // steps executing
    kPaused,        // temporarily suspended
    kSucceeded,     // all steps succeeded
    kFailed,        // at least one step failed permanently
    kCancelled,     // explicitly cancelled
};

inline std::string_view to_string(WorkflowRunState s) {
    switch (s) {
        case WorkflowRunState::kQueued:   return "queued";
        case WorkflowRunState::kRunning:  return "running";
        case WorkflowRunState::kPaused:   return "paused";
        case WorkflowRunState::kSucceeded:return "succeeded";
        case WorkflowRunState::kFailed:   return "failed";
        case WorkflowRunState::kCancelled:return "cancelled";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// WorkflowRun — Complete execution record of a workflow
// ---------------------------------------------------------------------------
struct WorkflowRun {
    std::string id;                  // unique run identifier
    std::string workflow_id;         // which workflow specification was used
    
    WorkflowRunState state = WorkflowRunState::kQueued;
    
    std::chrono::system_clock::time_point queued_at{};
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Step results (maintains history)
    std::vector<StepResult> step_results;
    
    // Overall outcome
    core::Outcome final_outcome;
};

// ---------------------------------------------------------------------------
// WorkflowNode — One node in a workflow DAG
// ---------------------------------------------------------------------------
struct WorkflowNode {
    std::string id;                  // unique node identifier
    
    // Step description
    work::ExecutionMode mode = work::ExecutionMode::kInline;
    std::optional<work::TaskId> task_id;  // optional task reference
    std::vector<std::pair<std::string, std::string>> parameters;
    
    // Dependencies: this node runs after all these nodes complete successfully
    std::vector<std::string> depends_on;
    
    // Retry configuration for this step
    int max_attempts = 1;
};

// ---------------------------------------------------------------------------
// WorkflowDefinition — Complete workflow specification (DAG + metadata)
// ---------------------------------------------------------------------------
struct WorkflowDefinition {
    std::string id;                  // unique identifier
    
    std::string title;
    std::string description;
    
    // Steps in the workflow DAG
    std::vector<WorkflowNode> nodes;
    
    // Entry/exit points (optional, inferred from graph if not specified)
    std::optional<std::string> start_node_id;
    std::optional<std::string> end_node_id;
};

// ---------------------------------------------------------------------------
// WorkflowValidator — Validates workflow definitions
// ---------------------------------------------------------------------------
class WorkflowValidator {
public:
    // Check for cycles in the dependency graph
    bool has_cycle(const std::vector<WorkflowNode>& nodes) const;
    
    // Validate all dependencies reference existing nodes
    std::vector<std::string> validate_dependencies(
        const std::vector<WorkflowNode>& nodes) const;
    
    // Compute a valid execution order (topological sort)
    std::optional<std::vector<std::string>> compute_execution_order(
        const std::vector<WorkflowNode>& nodes) const;
};

// ---------------------------------------------------------------------------
// WorkflowExecutor — Executes workflows using provided step handlers
// ---------------------------------------------------------------------------
class WorkflowExecutor {
public:
    using StepHandler = std::function<
        core::Outcome(const WorkflowNode&, CancellationToken& cancel_token)>;

    explicit WorkflowExecutor(StepHandler handler);

    // Execute a workflow, returning the final run record
    WorkflowRun execute(
        const WorkflowDefinition& definition,
        CancellationToken& cancel_token);
};

// ---------------------------------------------------------------------------
// Inline implementations
// ---------------------------------------------------------------------------

inline std::string to_string(const StepResult& r) {
    return "StepResult{" + r.step_id +
           ", status=" + std::string(to_string(r.status)) +
           ", attempt=" + std::to_string(r.attempt_number) + "}";
}

}  // namespace rebuntu::runtime