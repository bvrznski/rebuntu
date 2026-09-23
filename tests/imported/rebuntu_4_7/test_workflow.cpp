// Unit tests for Rebuntu Workflow contracts (Phase 0.11).
// Minimal, dependency-free assertion harness.

#include <system/core/contracts.hpp>
#include <system/runtime/workflow.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <set>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::core::SemanticStatus;
    using rebuntu::runtime::workflow::Step;
    using rebuntu::runtime::workflow::StepTargetKind;
    using rebuntu::runtime::workflow::ControlFlow;
    using rebuntu::runtime::workflow::BranchPolicy;
    using rebuntu::runtime::workflow::StepFailurePolicy;
    using rebuntu::runtime::workflow::WorkflowExecutionState;
    using rebuntu::runtime::workflow::WorkflowDefinition;
    using rebuntu::runtime::workflow::StepState;
    using rebuntu::runtime::workflow::to_string;
    using rebuntu::runtime::workflow::has_cycle;
    using rebuntu::runtime::workflow::validate_step_dependencies;
    using rebuntu::runtime::workflow::validate_workflow;

    std::cout << "Testing Phase 0.11 Workflow contracts...\n";

    // Test: StepTargetKind string conversions
    {
        CHECK(to_string(StepTargetKind::kUnit) == "unit");
        CHECK(to_string(StepTargetKind::kOperation) == "operation");
        CHECK(to_string(StepTargetKind::kWorkflow) == "workflow");
    }

    // Test: ControlFlow string conversions
    {
        CHECK(to_string(ControlFlow::kSequential) == "sequential");
        CHECK(to_string(ControlFlow::kConditional) == "conditional");
        CHECK(to_string(ControlFlow::kParallel) == "parallel");
    }

    // Test: BranchPolicy string conversions
    {
        CHECK(to_string(BranchPolicy::kAll) == "all");
        CHECK(to_string(BranchPolicy::kAny) == "any");
        CHECK(to_string(BranchPolicy::kFirstSuccess) == "first_success");
        CHECK(to_string(BranchPolicy::kQuorum) == "quorum");
    }

    // Test: StepFailurePolicy string conversions
    {
        CHECK(to_string(StepFailurePolicy::kFailFast) == "fail_fast");
        CHECK(to_string(StepFailurePolicy::kContinue) == "continue");
        CHECK(to_string(StepFailurePolicy::kSkipDependents) == "skip_dependents");
        CHECK(to_string(StepFailurePolicy::kCompensate) == "compensate");
    }

    // Test: WorkflowExecutionState string conversions
    {
        CHECK(to_string(WorkflowExecutionState::kPending) == "pending");
        CHECK(to_string(WorkflowExecutionState::kRunning) == "running");
        CHECK(to_string(WorkflowExecutionState::kPaused) == "paused");
        CHECK(to_string(WorkflowExecutionState::kSucceeded) == "succeeded");
        CHECK(to_string(WorkflowExecutionState::kFailed) == "failed");
        CHECK(to_string(WorkflowExecutionState::kCancelled) == "cancelled");
        CHECK(to_string(WorkflowExecutionState::kCompleted) == "completed");
    }

    // Test: Step construction
    {
        Step step;
        step.id = "step1";
        step.target_kind = StepTargetKind::kUnit;
        step.target_id = "package.install";

        CHECK(step.id == "step1");
        CHECK(step.target_kind == StepTargetKind::kUnit);
        CHECK(step.target_id == "package.install");
        CHECK(step.depends_on.size() == 0);
        CHECK(step.control_flow == ControlFlow::kSequential);
    }

    // Test: WorkflowDefinition construction
    {
        WorkflowDefinition wf;
        wf.id = "test.workflow";

        Step step1;
        step1.id = "step1";
        step1.target_kind = StepTargetKind::kUnit;
        step1.target_id = "unit1";

        Step step2;
        step2.id = "step2";
        step2.target_kind = StepTargetKind::kOperation;
        step2.target_id = "operation1";
        step2.depends_on.push_back("step1");

        wf.steps.push_back(step1);
        wf.steps.push_back(step2);

        CHECK(wf.id == "test.workflow");
        CHECK(wf.steps.size() == 2);
    }

    // Test: Validation - empty Workflow id
    {
        WorkflowDefinition wf;
        // id is empty by default

        auto issues = validate_workflow(wf);
        bool found_issue = false;
        for (const auto& issue : issues) {
            if (issue.find("missing id") != std::string::npos) {
                found_issue = true;
                break;
            }
        }
        CHECK(found_issue);
    }

    // Test: Validation - Step without target
    {
        WorkflowDefinition wf;
        wf.id = "test.workflow";

        Step step;
        step.id = "step1";
        // target_id is empty

        wf.steps.push_back(step);

        auto issues = validate_workflow(wf);
        bool found_issue = false;
        for (const auto& issue : issues) {
            if (issue.find("missing target_id") != std::string::npos) {
                found_issue = true;
                break;
            }
        }
        CHECK(found_issue);
    }

    // Test: Validation - unknown dependency
    {
        WorkflowDefinition wf;
        wf.id = "test.workflow";

        Step step1;
        step1.id = "step1";
        step1.target_kind = StepTargetKind::kUnit;
        step1.target_id = "unit1";

        Step step2;
        step2.id = "step2";
        step2.target_kind = StepTargetKind::kOperation;
        step2.target_id = "operation1";
        step2.depends_on.push_back("nonexistent");  // This doesn't exist

        wf.steps.push_back(step1);
        wf.steps.push_back(step2);

        auto issues = validate_workflow(wf);
        bool found_issue = false;
        for (const auto& issue : issues) {
            if (issue.find("depends on unknown Step") != std::string::npos) {
                found_issue = true;
                break;
            }
        }
        CHECK(found_issue);
    }

    // Test: WorkflowResult success
    {
        rebuntu::runtime::workflow::WorkflowResult result;
        result.status = SemanticStatus::kSuccess;
        result.verified = true;

        CHECK(result.success() == true);
        CHECK(result.status == SemanticStatus::kSuccess);
    }

    // Test: WorkflowResult not verified (should fail)
    {
        rebuntu::runtime::workflow::WorkflowResult result;
        result.status = SemanticStatus::kSuccess;
        result.verified = false;  // Not verified!

        CHECK(result.success() == false);  // Must be both success AND verified
    }

    // Test: StepState tracking with orthogonal state dimensions
    {
        StepState state;
        state.lifecycle = rebuntu::runtime::LifecycleState::kActive;
        state.work_state = rebuntu::runtime::WorkState::kProcessing;
        state.health_state = rebuntu::runtime::HealthState::kHealthy;
        state.recovery_state = rebuntu::runtime::RecoveryState::kNone;

        CHECK(state.lifecycle == rebuntu::runtime::LifecycleState::kActive);
        CHECK(state.work_state == rebuntu::runtime::WorkState::kProcessing);
    }

    // Test: ExecutionId construction
    {
        auto ids = rebuntu::runtime::ExecutionIds::make_root("request-123", "exec-456");

        CHECK(ids.request_id == "request-123");
        CHECK(ids.execution_id == "exec-456");
        CHECK(!ids.parent_execution_id.has_value());
    }

    // Test: Child ExecutionId
    {
        auto parent = rebuntu::runtime::ExecutionIds::make_root("req-1", "parent-1");
        auto child = rebuntu::runtime::ExecutionIds::make_child(parent, "child-2");

        CHECK(child.request_id == "req-1");           // Same root request
        CHECK(child.execution_id == "child-2");        // Different instance
        CHECK(child.parent_execution_id.has_value());
        CHECK(child.parent_execution_id.value() == "parent-1");  // Parent tracked
    }

    // Test: Cycle detection - linear chain (no cycle)
    {
        std::vector<Step> steps;

        Step s1; s1.id = "s1";
        Step s2; s2.id = "s2"; s2.depends_on.push_back("s1");
        Step s3; s3.id = "s3"; s3.depends_on.push_back("s2");

        steps.push_back(s1);
        steps.push_back(s2);
        steps.push_back(s3);

        CHECK(has_cycle(steps) == false);  // Linear chain has no cycle
    }

    // Test: Cycle detection - circular dependency
    {
        std::vector<Step> steps;

        Step s1; s1.id = "s1"; s1.depends_on.push_back("s3");
        Step s2; s2.id = "s2"; s2.depends_on.push_back("s1");
        Step s3; s3.id = "s3"; s3.depends_on.push_back("s2");

        steps.push_back(s1);
        steps.push_back(s2);
        steps.push_back(s3);

        CHECK(has_cycle(steps) == true);  // Circular dependency detected
    }

    // Test: validate_step_dependencies - all dependencies valid
    {
        std::vector<Step> steps;

        Step s1; s1.id = "s1";
        Step s2; s2.id = "s2"; s2.depends_on.push_back("s1");

        steps.push_back(s1);
        steps.push_back(s2);

        CHECK(validate_step_dependencies(steps) == true);
    }

    // Test: validate_step_dependencies - missing dependency
    {
        std::vector<Step> steps;

        Step s1; s1.id = "s1";
        Step s2; s2.id = "s2"; s2.depends_on.push_back("nonexistent");

        steps.push_back(s1);
        steps.push_back(s2);

        CHECK(validate_step_dependencies(steps) == false);
    }

    std::cout << "\nWorkflow contract tests completed.\n";

    return g_failures > 0 ? 1 : 0;
}
