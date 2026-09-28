// Rebuntu Retry Mechanics Unit Tests (Phase 6.24)
//
// Test the integrated retry mechanics with idempotency classification and state re-observation.

#include <vector>
#include <runtime/retry_mechanics.hpp>
#include <system/core/contracts.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::runtime;
using namespace rebuntu::core;

void test_retry_decision_abort_on_max_attempts() {
    RetryMechanics rm(2, std::chrono::milliseconds(100));
    
    Outcome outcome;
    outcome.status = SemanticStatus::kFailure;
    
    // At attempt 2 (max is 2), should abort
    auto decision = rm.decide(outcome, 2);
    assert(decision == RetryDecision::ABORT);
    std::cout << "PASS: Abort on max attempts\n";
}

void test_retry_decision_success_no_retry() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    Outcome outcome;
    outcome.status = SemanticStatus::kSuccess;
    
    auto decision = rm.decide(outcome, 0);
    assert(decision == RetryDecision::SKIP_RETRY);
    std::cout << "PASS: Success doesn't need retry\n";
}

void test_retry_decision_cancelled_no_retry() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    Outcome outcome;
    outcome.status = SemanticStatus::kCancelled;
    
    auto decision = rm.decide(outcome, 0);
    assert(decision == RetryDecision::ABORT);
    std::cout << "PASS: Cancelled doesn't retry\n";
}

void test_retry_decision_non_idempotent_aborts() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    OperationDefinition op;
    op.id = "test.non-idempotent";
    op.side_effect = SideEffectKind::DESTRUCTIVE;
    op.idempotency = Idempotency::NON_IDEMPOTENT;
    
    Outcome outcome;
    outcome.status = SemanticStatus::kFailure;
    
    // Non-idempotent operations should abort
    auto decision = rm.decide(outcome, 1, &op);
    assert(decision == RetryDecision::ABORT);
    std::cout << "PASS: Non-idempotent operation aborts\n";
}

void test_retry_decision_idempotent_allows() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    OperationDefinition op;
    op.id = "test.idempotent";
    op.side_effect = SideEffectKind::OBSERVATION;
    op.idempotency = Idempotency::IDEMPOTENT;
    
    Outcome outcome;
    outcome.status = SemanticStatus::kFailure;
    
    // Idempotent operations should allow retry
    auto decision = rm.decide(outcome, 1, &op);
    assert(decision == RetryDecision::RETRY);
    std::cout << "PASS: Idempotent operation allows retry\n";
}

void test_retry_decision_conditionally_idempotent_allows() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    OperationDefinition op;
    op.id = "test.conditionally-idempotent";
    op.side_effect = SideEffectKind::MUTATING;
    op.idempotency = Idempotency::CONDITIONALLY_IDEMPOTENT;
    
    Outcome outcome;
    outcome.status = SemanticStatus::kFailure;
    
    // Conditionally idempotent operations should allow retry
    auto decision = rm.decide(outcome, 1, &op);
    assert(decision == RetryDecision::RETRY);
    std::cout << "PASS: Conditionally-idempotent operation allows retry\n";
}

void test_retry_decision_without_op_def_allows() {
    RetryMechanics rm(3, std::chrono::milliseconds(100));
    
    Outcome outcome;
    outcome.status = SemanticStatus::kFailure;
    
    // Without op_def, default to allowing retry (caller can check state)
    auto decision = rm.decide(outcome, 1, nullptr);
    assert(decision == RetryDecision::RETRY);
    std::cout << "PASS: Default allows retry when no op_def\n";
}

void test_next_retry_delay_initial() {
    RetryMechanics rm(3, std::chrono::milliseconds(100), false);
    
    auto delay = rm.next_retry_delay(0);
    assert(delay == std::chrono::milliseconds(100));
    std::cout << "PASS: Initial retry delay is 100ms\n";
}

void test_next_retry_delay_exponential() {
    RetryMechanics rm(3, std::chrono::milliseconds(100), true);
    
    auto delay1 = rm.next_retry_delay(0);  // First retry
    assert(delay1 == std::chrono::milliseconds(100));
    
    auto delay2 = rm.next_retry_delay(1);  // Second retry
    assert(delay2 == std::chrono::milliseconds(200));  // 100 * 2^1
    
    auto delay3 = rm.next_retry_delay(2);  // Third retry
    assert(delay3 == std::chrono::milliseconds(400));  // 100 * 2^2
    
    auto delay_at_max = rm.next_retry_delay(3);  // At max, should be 0
    assert(delay_at_max == std::chrono::milliseconds(0));
    
    std::cout << "PASS: Exponential backoff delays correct\n";
}

void test_retry_observation_no_change() {
    auto obs = RetryObservation::no_change();
    assert(obs.state_changed == false);
    assert(obs.evidence.empty());
    std::cout << "PASS: no_change returns unchanged state\n";
}

void test_retry_observation_changed() {
    // Test that changed() creates a valid observation
    auto obs = RetryObservation::changed();
    assert(obs.state_changed == true);
    // evidence field is empty after move
    assert(obs.evidence.empty());
    std::cout << "PASS: changed returns changed state\n";
}

void test_retry_policy_from_idempotency() {
    auto policy = RetryPolicyBuilder::from_idempotency(Idempotency::IDEMPOTENT, 5);
    assert(policy.max_attempts >= 3);  // Should be at least 3 for idempotent
    
    std::cout << "PASS: from_idempotency creates policy\n";
}

void test_retry_policy_from_non_idempotent() {
    auto policy = RetryPolicyBuilder::from_idempotency(Idempotency::NON_IDEMPOTENT, 5);
    assert(policy.max_attempts == 1);  // Should be 1 for non-idempotent
    
    std::cout << "PASS: from_idempotency creates single-attempt policy for non-idempotent\n";
}

void test_max_retries_for_idempotency() {
    assert(RetryPolicyBuilder::max_retries_for_idempotency(Idempotency::IDEMPOTENT) == 3);
    assert(RetryPolicyBuilder::max_retries_for_idempotency(Idempotency::CONDITIONALLY_IDEMPOTENT) == 2);
    assert(RetryPolicyBuilder::max_retries_for_idempotency(Idempotency::NON_IDEMPOTENT) == 0);
    
    std::cout << "PASS: max_retries_for_idempotency returns correct values\n";
}

int main() {
    std::cout << "=== Retry Mechanics Unit Tests ===\n\n";
    
    test_retry_decision_abort_on_max_attempts();
    test_retry_decision_success_no_retry();
    test_retry_decision_cancelled_no_retry();
    test_retry_decision_non_idempotent_aborts();
    test_retry_decision_idempotent_allows();
    test_retry_decision_conditionally_idempotent_allows();
    test_retry_decision_without_op_def_allows();
    
    test_next_retry_delay_initial();
    test_next_retry_delay_exponential();
    
    test_retry_observation_no_change();
    test_retry_observation_changed();
    
    test_retry_policy_from_idempotency();
    test_retry_policy_from_non_idempotent();
    test_max_retries_for_idempotency();
    
    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}