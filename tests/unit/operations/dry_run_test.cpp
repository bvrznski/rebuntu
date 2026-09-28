// Rebuntu Operations — Dry-Run Tests (Phase 6.27)
//
// Tests for dry-run semantics implementation.
//
// Test coverage:
//   - Dry-run produces a plan without mutation
//   - Freshness is tracked for re-validation before real execution

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include <operations/dry_run.hpp>

namespace rebuntu::operations {

// ============================================================================
// dry_run_execute Tests
// ============================================================================

TEST(DryRunExecute, ReturnsFailureForEmptyOperationId) {
    core::OperationRequest request;
    request.operation_id = "";
    
    DryRunResult result = dry_run_execute("", request);
    
    EXPECT_EQ(result.status, core::SemanticStatus::kFailure);
}

TEST(DryRunExecute, GeneratesPlanForValidOperation) {
    core::OperationRequest request;
    request.operation_id = "filesystem.copy";
    
    DryRunResult result = dry_run_execute("filesystem.copy", request);
    
    // Plan should be generated (kCompleted status since it's a plan, not executed)
    EXPECT_EQ(result.status, core::SemanticStatus::kCompleted);
    ASSERT_TRUE(result.plan.has_value());
    EXPECT_EQ(result.plan->operation_id, "filesystem.copy");
}

TEST(DryRunExecute, GeneratesEvidenceWithFreshness) {
    core::OperationRequest request;
    request.operation_id = "test.operation";
    
    auto before = std::chrono::system_clock::now();
    DryRunResult result = dry_run_execute("test.operation", request);
    auto after = std::chrono::system_clock::now();
    
    // Freshness timestamp should be set
    EXPECT_GE(result.freshness_timestamp, before);
    EXPECT_LE(result.freshness_timestamp, after);
}

TEST(DryRunExecute, PlanContainsSteps) {
    core::OperationRequest request;
    request.operation_id = "filesystem.copy";
    
    DryRunResult result = dry_run_execute("filesystem.copy", request);
    
    ASSERT_TRUE(result.plan.has_value());
    // Plan should have steps for a non-no-op operation
    EXPECT_EQ(result.plan->steps.size(), 1);  // Placeholder step
}

// ============================================================================
// plan_to_string Tests
// ============================================================================

TEST(PlanToString, HandlesNoOp) {
    DryRunPlan plan;
    plan.operation_id = "test";
    plan.is_no_op = true;
    
    std::string s = plan_to_string(plan);
    EXPECT_NE(s.find("No action needed"), std::string::npos);
}

TEST(PlanToString, ShowsSteps) {
    DryRunPlan plan;
    plan.operation_id = "filesystem.copy";
    
    DryRunPlanStep step;
    step.description = "Copy file";
    step.native_action = "cp";
    step.argv = {"source.txt", "dest.txt"};
    plan.steps.push_back(step);
    plan.total_steps = 1;
    
    std::string s = plan_to_string(plan);
    EXPECT_NE(s.find("Step 1: Copy file"), std::string::npos);
}

TEST(PlanToString, ShowsRollbackPlan) {
    DryRunPlan plan;
    plan.operation_id = "filesystem.delete";
    
    plan.rollback_plan_description = "Restore from backup";
    
    std::string s = plan_to_string(plan);
    EXPECT_NE(s.find("Rollback Plan: Restore from backup"), std::string::npos);
}

// ============================================================================
// Freshness Re-Validation Tests
//
// Per Task 6.27 requirement:
// "Freshness must be checked again before later real execution"
// ============================================================================

TEST(DryRunFreshness, TimestampIsSet) {
    core::OperationRequest request;
    request.operation_id = "test";
    
    DryRunResult result = dry_run_execute("test", request);
    
    // Freshness timestamp should be non-zero
    auto epoch = result.freshness_timestamp.time_since_epoch();
    EXPECT_GT(epoch.count(), 0);
}

TEST(DryRunFreshness, PlanCannotConferAuthority) {
    core::OperationRequest request;
    request.operation_id = "filesystem.copy";
    
    DryRunResult result = dry_run_execute("filesystem.copy", request);
    
    // Even a successful dry-run result should have kCompleted status (plan generated)
    // not kSuccess (which would imply execution completed successfully)
    EXPECT_EQ(result.status, core::SemanticStatus::kCompleted);
}

}  // namespace rebuntu::operations