// Rebuntu Workflow Contracts (Phase 0.11)
// ========================================
//
// This establishes Rebuntu's canonical model for Workflow:
//
//   WORKFLOW =
//     A STRUCTURED COMPOSITION OF MULTIPLE BOUNDED ACTIONS OR OPERATIONS
//     WITH EXPLICIT CONTROL FLOW AND AN OVERALL PURPOSE.
//
// The key distinction:
//   - Automation: WHEN/WHY to execute work (trigger + policy)
//   - Workflow:   HOW coordinated work proceeds (steps, dependencies, control flow)
//   - Operation:  WHAT bounded system action is performed
//   - Unit:       Atomic/reusable executable definition that Steps invoke

#pragma once

#include <runtime/contracts.hpp>
#include <core/contracts.hpp>
#include <runtime/work.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <map>

namespace rebuntu::runtime {

// -----------------------------------------------------------------------------
// WorkflowTargetKind
// -----------------------------------------------------------------------------
// What kind of capability a Step references.
// -----------------------------------------------------------------------------

enum class WorkflowTargetKind {
    kUnit,          // References a Unit (reusable executable definition)
    kOperation,     // References an Operation (semantic contract)
    kWorkflow,      // Nested workflow invocation
};

inline std::string to_string(WorkflowTargetKind k) {
    switch (k) {
        case WorkflowTargetKind::kUnit:       return "unit";
        case WorkflowTargetKind::kOperation:  return "operation";
        case WorkflowTargetKind::kWorkflow:   return "workflow";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// StepFailurePolicy
// -----------------------------------------------------------------------------
// How a Step should behave when it fails.
// -----------------------------------------------------------------------------

enum class StepFailurePolicy {
    kFailFast,           // Stop entire Workflow immediately
    kContinue,           // Continue with remaining Steps (skip dependents)
    kSkipDependents,     // Skip Steps that depend on this one
    kCompensate,         // Attempt compensation/rollback actions
};

inline std::string to_string(StepFailurePolicy p) {
    switch (p) {
        case StepFailurePolicy::kFailFast:     return "fail_fast";
        case StepFailurePolicy::kContinue:     return "continue";
        case StepFailurePolicy::kSkipDependents: return "skip_dependents";
        case StepFailurePolicy::kCompensate:   return "compensate";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// StepControlFlow
// -----------------------------------------------------------------------------
// How a Step is executed relative to others.
// -----------------------------------------------------------------------------

enum class StepControlFlow {
    kSequential,   // Runs in sequence with other Steps
    kConditional,  // Branches based on condition
    kParallel,     // Runs concurrently when dependencies permit
};

inline std::string to_string(StepControlFlow f) {
    switch (f) {
        case StepControlFlow::kSequential: return "sequential";
        case StepControlFlow::kConditional: return "conditional";
        case StepControlFlow::kParallel: return "parallel";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// StepBranchPolicy
// -----------------------------------------------------------------------------
// How parallel branches converge at a join point.
// -----------------------------------------------------------------------------

enum class StepBranchPolicy {
    kAll,              // Wait for all branches
    kAny,              // Proceed when any branch completes
    kFirstSuccess,     // Proceed when first successful branch completes
    kFirstCompletion,  // Proceed when first branch completes (any outcome)
    kQuorum,           // Require minimum number of successful branches
};

inline std::string to_string(StepBranchPolicy p) {
    switch (p) {
        case StepBranchPolicy::kAll:            return "all";
        case StepBranchPolicy::kAny:            return "any";
        case StepBranchPolicy::kFirstSuccess:   return "first_success";
        case StepBranchPolicy::kFirstCompletion:return "first_completion";
        case StepBranchPolicy::kQuorum:         return "quorum";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Step
// -----------------------------------------------------------------------------
// The smallest orchestration node in a Workflow.
//
// A Step references an external capability (Unit/Operation) rather than
// containing implementation code. It provides metadata about execution:
// - dependencies on other Steps
// - conditions for execution
// - retry/timeout policies
// - failure handling strategy
// -----------------------------------------------------------------------------

struct Step {
    std::string id;                        // Unique within the Workflow
    
    WorkflowTargetKind target_kind;        // What kind of capability to invoke
    std::string target_id;                 // Identifier of the capability
    
    // Dependencies: which Steps must complete before this one runs
    std::vector<std::string> depends_on;
    
    // Condition: when this Step may execute (uses runtime::Condition)
    std::optional<runtime::Condition> condition;
    
    // Retry policy for this Step
    std::optional<core::RetryPolicy> retry_policy;
    
    // Timeout policy for this Step
    std::optional<core::TimeoutPolicy> timeout_policy;
    
    // Failure handling strategy
    StepFailurePolicy failure_policy = StepFailurePolicy::kFailFast;
    
    // Control flow mode for this Step
    StepControlFlow control_flow = StepControlFlow::kSequential;
    
    // How parallel branches converge (if this is a join point)
    StepBranchPolicy branch_policy = StepBranchPolicy::kAll;
    
    // Does this Step require post-execution verification?
    bool requires_verification = false;
};

// -----------------------------------------------------------------------------
// WorkflowDefinition
// -----------------------------------------------------------------------------
// Static specification of a Workflow. Immutable and reusable.
//
// A WorkflowDefinition contains Steps that reference Units/Operations,
// along with explicit dependencies, conditions, and failure handling policies.
// -----------------------------------------------------------------------------

struct WorkflowDefinition {
    std::string id;                        // Stable semantic identifier (e.g., "backup.verify")
    
    std::optional<std::string> title;
    std::optional<std::string> description;
    
    // Preconditions that must be satisfied before the Workflow can start
    std::vector<runtime::Condition> preconditions;
    
    // Steps that compose this Workflow
    std::vector<Step> steps;
    
    // Postconditions expected after successful execution
    std::vector<runtime::Condition> postconditions;
    
    // Does this Workflow allow parallel Step execution?
    bool allow_parallel = false;
    
    // Side effects classification (ComponentKind extension for workflow)
    core::ComponentKind side_effect = core::ComponentKind::kSystem;  // Default: no specific classification
    
    // Does this Workflow support checkpoint/resume?
    bool resumable = false;
    
    // Timeout for the entire Workflow (default from context if not set)
    std::optional<std::chrono::milliseconds> timeout;
};

// -----------------------------------------------------------------------------
// StepState
// -----------------------------------------------------------------------------
// Runtime state of a single Step within a WorkflowExecution.
// -----------------------------------------------------------------------------

enum class StepState {
    kPending,       // Not yet started
    kReady,         // Dependencies satisfied, ready to execute
    kRunning,       // Currently executing
    kCompleted,     // Successfully completed
    kFailed,        // Failed (may have retry history)
    kSkipped,       // Skipped due to failure in dependency or condition
    kCompensating,  // Compensation action in progress
};

inline std::string to_string(StepState s) {
    switch (s) {
        case StepState::kPending:      return "pending";
        case StepState::kReady:        return "ready";
        case StepState::kRunning:      return "running";
        case StepState::kCompleted:    return "completed";
        case StepState::kFailed:       return "failed";
        case StepState::kSkipped:      return "skipped";
        case StepState::kCompensating: return "compensating";
    }
    return "unknown";
}

struct StepExecution {
    std::string step_id;
    
    StepState state = StepState::kPending;
    
    // Timing
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Execution attempts (for retry semantics)
    int attempt_count = 0;
    int attempts_completed = 0;
    int attempts_pending = 0;
    
    // Result from the last execution
    core::Outcome outcome;  // Outcome of this Step's execution
    
    // Evidence collected during this Step
    std::vector<core::Evidence> evidence;
};

// -----------------------------------------------------------------------------
// WorkflowExecutionState
// -----------------------------------------------------------------------------

enum class WorkflowExecutionState {
    kCreated,       // Definition loaded, not yet started
    kPending,       // Precondition checks in progress
    kReady,         // Ready to begin execution
    kRunning,       // Steps are executing
    kSucceeded,     // All Steps completed successfully
    kFailed,        // Workflow terminated with failure
    kCancelled,     // Execution was cancelled
    kPaused,        // Execution is paused (for resumable Workflows)
};

inline std::string to_string(WorkflowExecutionState s) {
    switch (s) {
        case WorkflowExecutionState::kCreated:   return "created";
        case WorkflowExecutionState::kPending:   return "pending";
        case WorkflowExecutionState::kReady:     return "ready";
        case WorkflowExecutionState::kRunning:   return "running";
        case WorkflowExecutionState::kSucceeded: return "succeeded";
        case WorkflowExecutionState::kFailed:    return "failed";
        case WorkflowExecutionState::kCancelled: return "cancelled";
        case WorkflowExecutionState::kPaused:    return "paused";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// WorkflowExecution
// -----------------------------------------------------------------------------
// Runtime occurrence of a WorkflowDefinition.
//
// One WorkflowDefinition can have many WorkflowExecutions, each with its own
// state, evidence, and execution context.
// -----------------------------------------------------------------------------

struct WorkflowExecution {
    std::string execution_id;
    
    // Reference to the static definition
    std::optional<std::string> parent_execution_id;  // For nested invocations
    std::string definition_id;
    
    // Overall state
    WorkflowExecutionState state = WorkflowExecutionState::kCreated;
    
    // Runtime context
    RuntimeContext context;
    
    // Step execution tracking
    std::vector<StepExecution> step_executions;
    
    // Evidence collected during the entire Workflow
    std::vector<core::Evidence> evidence;
    
    // Timing
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Final result of the entire workflow
    core::Result final_result;  // Result with outcome and verification status
};

// -----------------------------------------------------------------------------
// WorkflowRegistry
// -----------------------------------------------------------------------------
// Data structure for managing WorkflowDefinitions.
//
// This is a static DATA structure and structural-integrity checker — NOT a
// runtime bus, event system, or service locator.
// -----------------------------------------------------------------------------

class WorkflowRegistry {
public:
    void register_workflow(WorkflowDefinition def) {
        workflows_[def.id] = std::move(def);
    }
    
    bool contains(std::string_view id) const {
        return workflows_.find(std::string{id}) != workflows_.end();
    }
    
    std::optional<WorkflowDefinition> find(std::string_view id) const {
        auto it = workflows_.find(std::string{id});
        if (it == workflows_.end()) return std::nullopt;
        return it->second;
    }
    
    std::size_t size() const { return workflows_.size(); }
    bool empty() const { return workflows_.empty(); }
    
    std::vector<WorkflowDefinition> all() const {
        std::vector<WorkflowDefinition> result;
        for (const auto& [id, wf] : workflows_) {
            result.push_back(wf);
        }
        std::sort(result.begin(), result.end(),
                  [](const WorkflowDefinition& a, const WorkflowDefinition& b) { return a.id < b.id; });
        return result;
    }

private:
    std::map<std::string, WorkflowDefinition> workflows_;
};

}  // namespace rebuntu::runtime