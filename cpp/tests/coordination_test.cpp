// rebuntu::runtime::coordination tests (Phase 4.7)
//
// Tests for the execution coordination interface.

#include <runtime/coordination/context.hpp>
#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::runtime::coordination;

void test_coordination_target_to_string() {
    std::cout << "Testing CoordinationTarget to_string...\n";
    
    assert(to_string(CoordinationTarget::kExecution) == "execution");
    assert(to_string(CoordinationTarget::kJob) == "job");
    assert(to_string(CoordinationTarget::kWorkflow) == "workflow");
    assert(to_string(CoordinationTarget::kResource) == "resource");
    assert(to_string(CoordinationTarget::kDependency) == "dependency");
    
    std::cout << "  coordination_target_to_string... PASS\n";
}

void test_coordination_result_status_to_string() {
    std::cout << "Testing CoordinationResultStatus to_string...\n";
    
    assert(to_string(CoordinationResultStatus::kAccepted) == "accepted");
    assert(to_string(CoordinationResultStatus::kPending) == "pending");
    assert(to_string(CoordinationResultStatus::kSuccess) == "success");
    assert(to_string(CoordinationResultStatus::kFailed) == "failed");
    assert(to_string(CoordinationResultStatus::kTimedOut) == "timed_out");
    assert(to_string(CoordinationResultStatus::kNotFound) == "not_found");
    assert(to_string(CoordinationResultStatus::kDeadlock) == "deadlock");
    assert(to_string(CoordinationResultStatus::kCancelled) == "cancelled");
    
    std::cout << "  coordination_result_status_to_string... PASS\n";
}

void test_coordination_operation_enum() {
    std::cout << "Testing CoordinationRequest::Operation enum...\n";
    
    // Test all operations exist
    assert(CoordinationRequest::Operation::kWaitFor != CoordinationRequest::Operation::kAcquire);
    assert(CoordinationRequest::Operation::kRelease != CoordinationRequest::Operation::kJoin);
    assert(CoordinationRequest::Operation::kHandoff != CoordinationRequest::Operation::kSignal);
    assert(CoordinationRequest::Operation::kBarrier != CoordinationRequest::Operation::kWaitFor);
    
    std::cout << "  coordination_operation_enum... PASS\n";
}

void test_coordination_request_fields() {
    std::cout << "Testing CoordinationRequest fields...\n";
    
    // Test CoordinationRequest struct
    CoordinationRequest req;
    req.id = "test-request";
    req.target_id = "target-1";
    req.operation = CoordinationRequest::Operation::kAcquire;
    
    assert(req.id == "test-request");
    assert(req.target_id == "target-1");
    assert(req.operation == CoordinationRequest::Operation::kAcquire);
    
    std::cout << "  coordination_request_fields... PASS\n";
}

void test_coordination_result_fields() {
    std::cout << "Testing CoordinationResult fields...\n";
    
    // Test CoordinationResult struct
    CoordinationResult result;
    result.request_id = "req-123";
    result.status = CoordinationResultStatus::kSuccess;
    
    assert(result.request_id == "req-123");
    assert(result.status == CoordinationResultStatus::kSuccess);
    
    std::cout << "  coordination_result_fields... PASS\n";
}

void test_coordinator_builder() {
    std::cout << "Testing CoordinatorBuilder...\n";
    
    // Test default builder
    CoordinatorBuilder builder;
    (void)builder;
    
    // Test with timeout
    CoordinatorBuilder builder_with_timeout = CoordinatorBuilder{}
        .set_default_timeout(std::chrono::milliseconds(10000));
    (void)builder_with_timeout;
    
    std::cout << "  coordinator_builder... PASS\n";
}

int main() {
    std::cout << "\n=== Phase 4.7: Coordination Tests ===\n\n";
    
    test_coordination_target_to_string();
    test_coordination_result_status_to_string();
    test_coordination_operation_enum();
    test_coordination_request_fields();
    test_coordination_result_fields();
    test_coordinator_builder();
    
    std::cout << "\nAll coordination tests passed!\n\n";
    
    return 0;
}