// Test for OperationEvidenceBundle (Phase 6.37)
//
// Bounded evidence tying request, resolved target, observations, plan,
// validation, execution result and verification together.

#include "src/runtime/native-command-operation-execution/subtask_targets/verification/operation_evidence_bundle_41581cb6.hpp"
#include "src/runtime/native-command-operation-execution/evidence_bundle.hpp"

#include <cassert>
#include <iostream>

int main() {
    // Test bounds
    rebuntu::runtime::native_command_operation_execution::EvidenceBundleBounds bounds;
    assert(bounds.max_evidence_records == 100);
    assert(bounds.max_plan_steps == 50);
    assert(bounds.max_observations_per_step == 10);
    
    // Test bundle creation
    rebuntu::runtime::native_command_operation_execution::OperationEvidenceBundle bundle(bounds);
    assert(!bundle.has_plan());
    assert(bundle.evidence().empty());
    
    // Test request and target resolution
    rebuntu::core::OperationRequest req;
    req.operation_id = "filesystem.copy";
    bundle.set_request(req);
    bundle.record_target_resolution("/tmp/test.txt");
    assert(bundle.request().operation_id == "filesystem.copy");
    
    // Test plan
    rebuntu::platform::v0040::ChangePlan plan;
    plan.id = "test-plan";
    plan.domain = "filesystem";
    plan.steps.push_back("step1");
    bundle.set_plan(plan);
    assert(bundle.has_plan());
    
    // Test evidence trimming with bounded evidence
    rebuntu::runtime::native_command_operation_execution::EvidenceBundleBounds small_bounds;
    small_bounds.max_evidence_records = 3;
    rebuntu::runtime::native_command_operation_execution::OperationEvidenceBundle small_bundle(small_bounds);
    
    rebuntu::platform::v0040::Evidence e1{"src1", "val1", rebuntu::platform::v0040::Epistemic::observed};
    rebuntu::platform::v0040::Evidence e2{"src2", "val2", rebuntu::platform::v0040::Epistemic::observed};
    rebuntu::platform::v0040::Evidence e3{"src3", "val3", rebuntu::platform::v0040::Epistemic::observed};
    rebuntu::platform::v0040::Evidence e4{"src4", "val4", rebuntu::platform::v0040::Epistemic::observed};
    
    std::vector<rebuntu::platform::v0040::Evidence> obs = {e1, e2, e3, e4};
    small_bundle.record_initial_observations(obs);
    assert(small_bundle.evidence_count() <= small_bounds.max_evidence_records);
    
    // Test builder
    rebuntu::runtime::native_command_operation_execution::EvidenceBundleBuilder builder(bounds);
    builder.set_request(req)
           .set_plan(plan);
    
    rebuntu::runtime::native_command_operation_execution::ValidationBundle validation;
    validation.preconditions_satisfied = true;
    builder.set_validation(validation);
    
    auto built_bundle = builder.build();
    assert(built_bundle.has_plan());
    assert(built_bundle.request().operation_id == "filesystem.copy");
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}