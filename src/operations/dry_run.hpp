// Rebuntu Operations — Dry-Run Semantics (Phase 6.27)
//
// Dry-run semantics for operations: produces a plan/explanation without mutation.
//
// Key principles:
//   - Dry-run must NOT execute then undo
//   - Dry-run generates a plan first, then reports what WOULD happen
//   - Freshness must be re-checked before real execution (dry-run result is not fresh)
//   - Plan is immutable and cannot confer authority

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>
#include <planning/change_planner.hpp>
#include <chrono>
#include <string>
#include <vector>
#include <optional>

namespace rebuntu::operations {

// ============================================================================
// DryRunPlanStep — A single step in a dry-run execution plan
//
// This describes what would happen if the operation were executed,
// without actually making any mutations.
// ============================================================================

struct DryRunPlanStep {
    std::string description;           // Human-readable description of the step
    std::string native_action;         // Native mechanism to invoke (e.g., "cp", "mkdir")
    std::vector<std::string> argv;     // Argument vector for the action
    
    // Expected state before this step
    std::optional<std::string> expected_before_state;
    
    // Expected state after this step (if successful)
    std::optional<std::string> expected_after_state;
    
    // Verification that would be performed
    bool requires_verification = false;
    
    // Side effect classification for user understanding
    core::SideEffectKind side_effect = core::SideEffectKind::NONE;
};

// ============================================================================
// DryRunPlan — Complete execution plan for a dry-run operation
//
// This is the result of a dry-run: what would happen, not what happened.
// ============================================================================

struct DryRunPlan {
    std::string operation_id;          // Which operation this plans
    
    // Overall strategy
    bool is_no_op = false;             // No action needed (preconditions already met)
    
    // Steps that would be executed
    std::vector<DryRunPlanStep> steps;
    
    // Rollback plan description (if operation is reversible)
    std::optional<std::string> rollback_plan_description;
    
    // Verification strategy for post-execution
    std::vector<std::string> verification_steps;
    
    // Summary statistics
    int total_steps = 0;
    size_t estimated_cost_bytes = 0;   // Estimated resource usage
};

// ============================================================================
// DryRunResult — Result of a dry-run operation
//
// This carries the plan (what would happen) and evidence supporting it.
// The result does NOT mutate any state.
// ============================================================================

struct DryRunResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    // Plan describing what would happen on real execution
    std::optional<DryRunPlan> plan;
    
    // Evidence: observations supporting the plan
    std::vector<core::Evidence> evidence;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Freshness metadata (when this dry-run was performed)
    std::chrono::system_clock::time_point freshness_timestamp =
        std::chrono::system_clock::now();
    
    static DryRunResult no_change() {
        // No action needed: desired state already exists
        DryRunResult r;
        r.status = core::SemanticStatus::kSuccess;
        DryRunPlan plan{};
        plan.is_no_op = true;
        r.plan = std::move(plan);
        return r;
    }
    
    static DryRunResult with_plan(DryRunPlan p) {
        DryRunResult r;
        r.status = core::SemanticStatus::kCompleted;  // Plan generated, not executed
        r.plan = std::move(p);
        return r;
    }
    
    static DryRunResult failure(std::string code, std::string message) {
        DryRunResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

// ============================================================================
// dry_run_execute — Generate a dry-run plan without mutation
//
// Precondition:
//   - Operation inputs are valid
//   - Current state can be observed
//
// Postcondition:
//   - NO state is mutated during dry-run
//   - Plan describes what WOULD happen on real execution
//   - Freshness timestamp marks when this observation was made
//
// The caller must re-validate and re-check freshness before executing.
// ============================================================================

DryRunResult dry_run_execute(
    const std::string& operation_id,
    const core::OperationRequest& request);

// ============================================================================
// plan_to_string — Convert a DryRunPlan to human-readable explanation
// ============================================================================

std::string plan_to_string(const DryRunPlan& plan);

}  // namespace rebuntu::operations