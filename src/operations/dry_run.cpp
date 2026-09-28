// Rebuntu Operations — Dry-Run Semantics Implementation (Phase 6.27)
//
// This implements dry-run semantics for operations: produces a plan/explanation
// without mutation.
//
// Key principles:
//   - Dry-run must NOT execute then undo
//   - Dry-run generates a plan first, then reports what WOULD happen
//   - Freshness must be re-checked before real execution (dry-run result is not fresh)
//   - Plan is immutable and cannot confer authority

#include <operations/dry_run.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::operations {

// ============================================================================
// plan_to_string — Convert a DryRunPlan to human-readable explanation
// ============================================================================

std::string plan_to_string(const DryRunPlan& plan) {
    std::string result = "Dry-Run Plan for: " + plan.operation_id + "\n";
    
    if (plan.is_no_op) {
        result += "  Status: No action needed - desired state already exists\n";
        return result;
    }
    
    result += "  Steps:\n";
    for (size_t i = 0; i < plan.steps.size(); ++i) {
        const auto& step = plan.steps[i];
        result += "    Step " + std::to_string(i + 1) + ": " + step.description + "\n";
        result += "      Action: " + step.native_action;
        if (!step.argv.empty()) {
            result += " [";
            for (size_t j = 0; j < step.argv.size(); ++j) {
                if (j > 0) result += ", ";
                result += step.argv[j];
            }
            result += "]";
        }
        result += "\n";
        
        if (step.side_effect != core::SideEffectKind::NONE) {
            result += "      Side Effect: " + std::string(core::to_string(step.side_effect)) + "\n";
        }
    }
    
    result += "  Total steps: " + std::to_string(plan.steps.size()) + "\n";
    
    if (plan.rollback_plan_description.has_value()) {
        result += "  Rollback Plan: " + *plan.rollback_plan_description + "\n";
    }
    
    return result;
}

// ============================================================================
// dry_run_execute — Generate a dry-run plan without mutation
//
// This is the core implementation that:
//   1. Observes current state (no mutation)
//   2. Evaluates preconditions (no mutation)  
//   3. Builds an execution plan (no mutation)
//   4. Returns the plan with evidence
//
// The caller must re-validate and re-check freshness before executing.
// ============================================================================

DryRunResult dry_run_execute(
    const std::string& operation_id,
    const core::OperationRequest& /* request */) {
    
    // Note: This is a minimal implementation for Phase 6.27 demonstration.
    // Full implementation would:
    //   - Query the OperationRegistry to find the operation definition
    //   - Evaluate preconditions against current state
    //   - Build an execution plan with native Linux mechanisms
    //   - Return a DryRunPlan with step-by-step details
    
    // For now, we handle common cases
    if (operation_id.empty()) {
        return DryRunResult::failure("E_INVALID_OPERATION", "Operation ID is empty");
    }
    
    // Check for no-op case: if the desired state already matches current state
    // This requires observing current state first
    bool is_no_op = false;  // In real implementation, this would be based on observation
    
    DryRunPlan plan;
    plan.operation_id = operation_id;
    plan.is_no_op = is_no_op;
    
    if (is_no_op) {
        return DryRunResult::no_change();
    }
    
    // Add placeholder steps
    DryRunPlanStep step;
    step.description = "Placeholder: Operation would execute with dry_run=true";
    step.native_action = "operation:" + operation_id;
    step.requires_verification = true;
    
    plan.steps.push_back(std::move(step));
    plan.total_steps = static_cast<int>(plan.steps.size());
    
    // Generate evidence of the observation
    core::Evidence e;
    e.source = "dry_run_planner";
    e.value = "Dry-run plan generated for operation: " + operation_id;
    auto now = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", gmtime(&tt));
    e.captured_at = std::string(buf);
    
    DryRunResult result;
    result.status = core::SemanticStatus::kCompleted;  // Plan generated, not executed
    result.plan = std::move(plan);
    result.evidence.push_back(std::move(e));
    
    return result;
}

}  // namespace rebuntu::operations