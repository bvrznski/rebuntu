// rebuntu::runtime::workflow — Workflow architecture (Phase 0.11)
//
// This header establishes Rebuntu's Workflow composition model:
// how multiple Operations/Units are orchestrated toward an objective.
//
// Key principles:
//   * WORKFLOW = COMPOSITION OF MULTIPLE BOUNDED ACTIONS WITH CONTROL FLOW
//   * WorkflowDefinition (static) vs WorkflowExecution (runtime)
//   * Step as the smallest orchestration node (references Units/Operations)
//   * Control flow: sequential, conditional, parallel branches
//   * Integration with existing contracts: Outcome, Result, State dimensions
//
// Distinctions:
//   * Workflow != Operation (Operation is atomic; Workflow orchestrates multiple)
//   * Workflow != Task (Task parameterizes an Operation; Workflow composes many)
//   * Workflow != Automation (Automation triggers WHEN; Workflow defines WHAT)
//   * Workflow != Schedule (Schedule specifies WHEN to run; Workflow defines WHAT)
//   * Workflow != Script (Script is executable artifact; Workflow is definition)

#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/contracts.hpp>
#include <algorithm>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::workflow {

// ---------------------------------------------------------------------------
// StepTargetKind
// What kind of target a Step invokes.
// ---------------------------------------------------------------------------
enum class StepTargetKind {
    kUnit,          // References a Unit (reusable executable definition)
    kOperation,     // References an Operation (contractual capability)
    kWorkflow,      // References another Workflow (composition)
};

inline std::string_view to_string(StepTargetKind k) {
    switch (k) {
        case StepTargetKind::kUnit:       return "unit";
        case StepTargetKind::kOperation:  return "operation";
        case StepTargetKind::kWorkflow:   return "workflow";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// ControlFlow
// How Steps are ordered and related.
// ---------------------------------------------------------------------------
enum class ControlFlow {
    kSequential,    // A -> B -> C (each waits for previous)
    kConditional,   // A -> [condition] -> B | C (branch)
    kParallel,      // A, B run concurrently; then C
};

inline std::string_view to_string(ControlFlow f) {
    switch (f) {
        case ControlFlow::kSequential: return "sequential";
        case ControlFlow::kConditional: return "conditional";
        case ControlFlow::kParallel:    return "parallel";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// BranchPolicy
// How parallel branches converge.
// ---------------------------------------------------------------------------
enum class BranchPolicy {
    kAll,              // Wait for all branches to complete
    kAny,              // Proceed when any branch completes
    kFirstSuccess,     // Proceed when first successful branch completes
    kQuorum,           // Require N branches to succeed (N configurable)
};

inline std::string_view to_string(BranchPolicy p) {
    switch (p) {
        case BranchPolicy::kAll:         return "all";
        case BranchPolicy::kAny:         return "any";
        case BranchPolicy::kFirstSuccess:return "first_success";
        case BranchPolicy::kQuorum:      return "quorum";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// StepFailurePolicy
// What happens when a Step fails.
// ---------------------------------------------------------------------------
enum class StepFailurePolicy {
    kFailFast,          // Stop entire Workflow immediately
    kContinue,          // Continue with remaining Steps (skip dependents)
    kSkipDependents,    // Skip Steps that depend on this one
    kCompensate,        // Attempt compensation/rollback actions
};

inline std::string_view to_string(StepFailurePolicy p) {
    switch (p) {
        case StepFailurePolicy::kFailFast:       return "fail_fast";
        case StepFailurePolicy::kContinue:       return "continue";
        case StepFailurePolicy::kSkipDependents: return "skip_dependents";
        case StepFailurePolicy::kCompensate:     return "compensate";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// StepCondition
// A condition that must be satisfied for a Step to execute.
// Uses the existing runtime::Condition type from contracts.hpp.
// ---------------------------------------------------------------------------
using Condition = runtime::Condition;

// ---------------------------------------------------------------------------
// Step
// The smallest orchestration node in a Workflow.
//
// A Step does NOT contain implementation code. It references an external
// executable capability (Unit, Operation, or nested Workflow) and provides
// metadata about how to invoke and coordinate it.
// ---------------------------------------------------------------------------
struct Step {
    std::string id;                    // Unique identifier within the Workflow
    
    std::optional<std::string> name;   // Human-readable label (optional)
    
    // Target: what this Step invokes
    StepTargetKind target_kind;
    std::string target_id;             // ID of Unit/Operation/Workflow to invoke
    
    // Parameters passed to the target
    std::vector<std::pair<std::string, std::string>> parameters;
    
    // Dependencies: which Steps must complete before this one runs
    std::vector<std::string> depends_on;
    
    // Control flow configuration
    ControlFlow control_flow = ControlFlow::kSequential;
    BranchPolicy branch_policy = BranchPolicy::kAll;
    int quorum_count = 1;              // Used when branch_policy == kQuorum
    
    // Conditions: when this Step can execute
    std::optional<Condition> condition;  // Precondition for execution
    
    // Execution controls
    runtime::RetryPolicy retry_policy;
    runtime::TimeoutPolicy timeout_policy;
    
    StepFailurePolicy failure_policy = StepFailurePolicy::kFailFast;
    
    // Input/Output bindings: how outputs from previous Steps become inputs
    std::optional<std::string> input_from;      // Step ID whose output becomes input
    std::optional<std::string> output_as;       // Name this Step's output will have
    
    // Verification: post-execution verification (uses existing Outcome/Result model)
    bool requires_verification = false;
    
    // Compensation: action to take if this Step fails
    std::optional<std::string> compensation_step_id;
};

// ---------------------------------------------------------------------------
// WorkflowDefinition
// A static specification describing how Steps are composed toward an objective.
//
// This is NOT executable code. It's a data structure that:
//   * Defines the orchestration topology (which Steps, how they relate)
//   * References external capabilities (Units/Operations) via their IDs
//   * Specifies control flow semantics (sequential, conditional, parallel)
//   * Embeds retry/timeout policies per Step
//
// A WorkflowDefinition may be invoked multiple times, producing different
// WorkflowExecution instances. The definition itself is immutable.
// ---------------------------------------------------------------------------
struct WorkflowDefinition {
    std::string id;                    // Stable semantic identifier
                                       // Example: "system.backup.verify"
    
    std::optional<std::string> title;
    std::optional<std::string> description;
    
    // Precondition: must be true before Workflow starts
    std::optional<Condition> preconditions;
    
    // Expected effects: what this Workflow is meant to change
    std::vector<std::string> expected_effects;
    
    // Postcondition: must be true for success (uses Outcome/Result model)
    std::vector<Condition> postconditions;
    
    // Steps: the orchestration nodes
    std::vector<Step> steps;
    
    // Control flow at Workflow level
    bool allow_parallel = false;       // Allow parallel Step execution
    
    // State dimensions (orthogonal runtime attributes)
    bool is_read_only = false;         // Does not mutate system state
    bool requires_privilege = false;   // Requires elevated privilege
    
    // Safety characteristics
    core::SideEffectKind side_effect = core::SideEffectKind::NONE;
    core::Idempotency idempotency = core::Idempotency::UNKNOWN;
    core::Reversibility reversibility = core::Reversibility::UNKNOWN;
    
    // Persistence: can this execution be resumed?
    bool resumable = false;            // Supports checkpoint/resume
};

// ---------------------------------------------------------------------------
// StepState
// Runtime state for a single Step within an execution.
// Uses orthogonal state dimensions from runtime contracts.
// ---------------------------------------------------------------------------
struct StepState {
    runtime::LifecycleState lifecycle;
    runtime::WorkState work_state;
    runtime::HealthState health_state;
    runtime::RecoveryState recovery_state;
    
    std::chrono::system_clock::time_point timestamp;
    
    // Execution tracking
    int attempt_number = 0;            // Which retry/attempt this is
    
    // Outcome (uses existing core contracts)
    core::SemanticStatus outcome_status = core::SemanticStatus::kUnknown;
    bool verified = false;
    
    // Step-specific results
    std::optional<std::string> step_output;   // Output from executing the target
};

// ---------------------------------------------------------------------------
// WorkflowExecutionState
// Runtime state for a complete Workflow execution.
// ---------------------------------------------------------------------------
enum class WorkflowExecutionState {
    kPending,       // Created but not yet started
    kRunning,       // Steps are executing
    kPaused,        // Execution suspended (e.g., for checkpoint)
    kSucceeded,     // All Steps succeeded and postconditions verified
    kFailed,        // Execution terminated with failure
    kCancelled,     // Explicitly cancelled
    kCompleted,     // Execution finished (may not be verified/successful)
};

inline std::string_view to_string(WorkflowExecutionState s) {
    switch (s) {
        case WorkflowExecutionState::kPending:   return "pending";
        case WorkflowExecutionState::kRunning:   return "running";
        case WorkflowExecutionState::kPaused:    return "paused";
        case WorkflowExecutionState::kSucceeded: return "succeeded";
        case WorkflowExecutionState::kFailed:    return "failed";
        case WorkflowExecutionState::kCancelled: return "cancelled";
        case WorkflowExecutionState::kCompleted: return "completed";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// WorkflowExecution
// A runtime occurrence of a WorkflowDefinition.
//
// Contains:
//   * Identity: which definition, which instance, correlation IDs
//   * Runtime state: per-step execution tracking
//   * Timing: when started, when each Step completed
//   * Results: per-Step outcomes with verification status and evidence
// ---------------------------------------------------------------------------
struct WorkflowExecution {
    std::string execution_id;          // Unique runtime instance ID
    
    // Correlation with parent chain
    std::optional<std::string> parent_execution_id;
    
    // Definition reference (which Workflow is running)
    std::string definition_id;
    std::chrono::system_clock::time_point created_at;
    
    // Runtime state
    WorkflowExecutionState state = WorkflowExecutionState::kPending;
    
    // Timing
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Per-step runtime state
    std::vector<StepState> step_states;
    
    // Results: Outcome/Result with verification and evidence (uses core contracts)
    // Each Step produces a Result; the Workflow result aggregates them.
    
    // Error information (if not success)
    std::optional<std::string> failure_reason;
    std::optional<std::string> failure_step_id;
    
    // Verification status
    bool postconditions_verified = false;
    
    // Evidence: observations supporting the outcome
    std::vector<core::Evidence> evidence;
};

// ---------------------------------------------------------------------------
// WorkflowResult
// The final result of a Workflow execution.
//
// Uses existing Outcome/Result model but aggregates Step-level results.
// ---------------------------------------------------------------------------
struct WorkflowResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    // Verification: were postconditions independently verified?
    bool verified = false;
    
    // Timing
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point completed_at;
    std::chrono::milliseconds total_duration_ms{0};
    
    // Per-step results (aggregated)
    struct StepResult {
        std::string step_id;
        core::SemanticStatus status;
        bool verified;
        std::vector<core::Evidence> evidence;
        std::optional<std::string> output_value;
        std::chrono::milliseconds duration_ms{0};
    };
    
    std::vector<StepResult> step_results;
    
    // Overall outcome
    bool success() const {
        return status == core::SemanticStatus::kSuccess && verified;
    }
};

// ---------------------------------------------------------------------------
// WorkflowContext
// Runtime context passed to each Step during execution.
//
// Contains information about:
//   * The current execution instance
//   * Input data (from previous Steps, parameters, or environment)
//   * Cancellation signals
//   * Deadlines
// ---------------------------------------------------------------------------
struct WorkflowContext {
    ExecutionIds exec_ids;             // Correlation IDs
    
    std::optional<std::string> caller_id;   // Who initiated this execution
    
    // Runtime state input (output from previous Steps, parameters, etc.)
    std::map<std::string, std::string> inputs;
    
    // Cancellation
    bool cancellation_requested = false;
    std::chrono::system_clock::time_point deadline;
    
    // Evidence collection
    std::vector<core::Evidence>& evidence;  // Reference to accumulate evidence
    
    WorkflowContext(ExecutionIds ids, 
                    std::chrono::system_clock::time_point dl,
                    std::vector<core::Evidence>& ev)
        : exec_ids(ids), deadline(dl), evidence(ev) {}
};

// ---------------------------------------------------------------------------
// Validation helpers
// ---------------------------------------------------------------------------

inline bool has_cycle(const std::vector<Step>& steps) {
    // Simple cycle detection: for each Step, check if its dependencies
    // would create a path back to itself.
    // This is O(n^2); for large graphs, use proper topological sort.
    
    std::set<std::string> step_ids;
    for (const auto& s : steps) {
        step_ids.insert(s.id);
    }
    
    // For each Step, trace its dependency chain
    for (const auto& s : steps) {
        std::set<std::string> visited;
        std::vector<std::string> stack = s.depends_on;
        
        while (!stack.empty()) {
            auto dep_id = stack.back();
            stack.pop_back();
            
            if (dep_id == s.id) {
                return true;  // Cycle detected
            }
            
            if (visited.contains(dep_id)) {
                continue;
            }
            visited.insert(dep_id);
            
            // Find the Step with this ID and add its dependencies
            for (const auto& other : steps) {
                if (other.id == dep_id) {
                    stack.insert(stack.end(), 
                                other.depends_on.begin(),
                                other.depends_on.end());
                    break;
                }
            }
        }
    }
    
    return false;
}

inline bool validate_step_dependencies(const std::vector<Step>& steps) {
    // Every dependency must reference an existing Step
    std::set<std::string> step_ids;
    for (const auto& s : steps) {
        step_ids.insert(s.id);
    }
    
    for (const auto& s : steps) {
        for (const auto& dep : s.depends_on) {
            if (!step_ids.contains(dep)) {
                return false;  // Dependency references non-existent Step
            }
        }
    }
    
    return true;
}

inline std::vector<std::string> validate_workflow(const WorkflowDefinition& wf) {
    std::vector<std::string> issues;
    
    if (wf.id.empty()) {
        issues.push_back("WorkflowDefinition missing id");
    }
    
    // Validate Steps
    for (const auto& step : wf.steps) {
        if (step.id.empty()) {
            issues.push_back("Step missing id");
        }
        
        if (step.target_id.empty()) {
            issues.push_back("Step " + step.id + " missing target_id");
        }
        
        // Check dependencies
        for (const auto& dep : step.depends_on) {
            bool found = false;
            for (const auto& s : wf.steps) {
                if (s.id == dep) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                issues.push_back("Step " + step.id + " depends on unknown Step: " + dep);
            }
        }
    }
    
    // Check for cycles
    if (has_cycle(wf.steps)) {
        issues.push_back("Workflow contains dependency cycle");
    }
    
    return issues;
}

}  // namespace rebuntu::runtime::workflow

// ---------------------------------------------------------------------------
// Integration with core contracts
// ---------------------------------------------------------------------------

namespace rebuntu::core {

// WorkflowResult can be used where Outcome is expected
// by treating the overall workflow status as the semantic outcome.

}  // namespace rebuntu::core
