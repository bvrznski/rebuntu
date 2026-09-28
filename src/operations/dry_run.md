# Rebuntu Operations — Dry-Run Semantics (Phase 6.27)

## Overview

This module implements dry-run semantics for Rebuntu operations. Dry-run produces a plan/explanation without mutation.

### Key Principles

1. **Dry-run must NOT execute then undo** - This is critical. The implementation generates a plan FIRST, then reports what WOULD happen. It never executes and reverses actions.

2. **Freshness must be re-checked before real execution** - A dry-run result captures system state at a point in time. When executing later, the caller MUST re-observe current state to ensure it's still valid for execution.

3. **Plan is immutable and cannot confer authority** - The plan describes intent, not permission. Authorization checks are separate from planning.

## API

### DryRunResult

The result of a dry-run operation:

```cpp
struct DryRunResult {
    core::SemanticStatus status;        // kCompleted (plan generated), kSuccess (no-op), or kFailure
    std::optional<DryRunPlan> plan;     // The generated execution plan
    std::vector<core::Evidence> evidence;  // Observations supporting the plan
    std::optional<core::Error> error;   // Error information if failure
    std::chrono::system_clock::time_point freshness_timestamp;  // When observation was made
};
```

### DryRunPlan

The complete execution plan:

```cpp
struct DryRunPlan {
    std::string operation_id;           // Which operation this plans
    bool is_no_op;                      // True if no action needed
    std::vector<DryRunPlanStep> steps;  // Steps that would be executed
    std::optional<std::string> rollback_plan_description;
    std::vector<std::string> verification_steps;
    int total_steps;
    size_t estimated_cost_bytes;
};
```

### DryRunPlanStep

A single step in the plan:

```cpp
struct DryRunPlanStep {
    std::string description;            // Human-readable description
    std::string native_action;          // Native mechanism to invoke (e.g., "cp", "mkdir")
    std::vector<std::string> argv;      // Argument vector for the action
    std::optional<std::string> expected_before_state;
    std::optional<std::string> expected_after_state;
    bool requires_verification;
    core::SideEffectKind side_effect;
};
```

## Usage

```cpp
// Generate a dry-run plan without mutation
core::OperationRequest request;
request.operation_id = "filesystem.copy";
request.parameters["source"] = "/path/to/source";
request.parameters["destination"] = "/path/to/dest";

DryRunResult result = dry_run_execute("filesystem.copy", request);

if (result.status == core::SemanticStatus::kCompleted && result.plan.has_value()) {
    // Print the plan for user review
    std::cout << plan_to_string(*result.plan);
    
    // User confirms - NOW re-check freshness before executing
    // The dry-run observation is now stale; must re-observe current state
    
    // ... perform actual execution with fresh observations ...
}
```

## Freshness Semantics

The `freshness_timestamp` field marks when the observation was made. Before executing:

1. Re-query current system state
2. Compare with the state at `freshness_timestamp`
3. If there are significant changes, regenerate the plan or abort
4. Only then execute with fresh observations

## Implementation Notes

- The minimal implementation in this module demonstrates the dry-run pattern
- Full integration would:
  - Query the OperationRegistry to find operation definitions
  - Evaluate preconditions against current state
  - Build execution plans using native Linux mechanisms (systemd, procfs, D-Bus, etc.)
  - Return detailed step-by-step plans with expected before/after states

## Integration Points

- `OperationRequest::dry_run` field already exists in contracts.hpp (line 917)
- Operations should check this flag and either:
  - Execute normally when false
  - Generate a plan without mutation when true
- The result uses `kCompleted` status (plan generated, not executed)