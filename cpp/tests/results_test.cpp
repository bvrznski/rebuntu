// rebuntu::core::results - Phase 0.17 Result/Outcome/Error model tests
//
// Tests canonical definitions for:
//   - SemanticStatus vs VerificationStatus distinction
//   - ExecutionResult<T> and ExecutionResult<void>
//   - Evidence collection with provenance
//   - Retry aggregation preserving history

#include <runtime/core/results.hpp>
#include <cassert>
#include <iostream>
#include <string>

using namespace rebuntu::core;

void test_semantic_status() {
    // Test SemanticStatus enum values
    assert(to_string(SemanticStatus::kSuccess) == "success");
    assert(to_string(SemanticStatus::kCompleted) == "completed");
    assert(to_string(SemanticStatus::kFailure) == "failure");
    assert(to_string(SemanticStatus::kUnknown) == "unknown");
    assert(to_string(SemanticStatus::kCancelled) == "cancelled");
}

void test_verification_status() {
    // Test VerificationStatus enum values
    assert(to_string(VerificationStatus::kVerified) == "verified");
    assert(to_string(VerificationStatus::kNotVerified) == "not_verified");
    assert(to_string(VerificationStatus::kVerificationFailed) == "verification_failed");
    assert(to_string(VerificationStatus::kUnknown) == "unknown");
}

void test_execution_outcome() {
    // Test success outcome
    ExecutionOutcome so = ExecutionOutcome::success();
    assert(so.status == SemanticStatus::kSuccess);
    assert(so.succeeded());
    assert(so.is_completed());

    // Test completed state (not verified)
    ExecutionOutcome co = ExecutionOutcome::completed_state();
    assert(co.status == SemanticStatus::kCompleted);
    assert(!co.succeeded());  // not verified
    assert(co.is_completed());

    // Test failure outcome
    ExecutionOutcome fo = ExecutionOutcome::failure();
    assert(fo.status == SemanticStatus::kFailure);
    assert(fo.failed());
}

void test_verification_result() {
    // Create evidence for testing (using contract definition)
    Evidence e{"procfs", "value", "2024-01-01T00:00:00Z"};
    
    // Test verified
    VerificationResult vr = VerificationResult::verified(e);
    assert(vr.status == VerificationStatus::kVerified);
    assert(!vr.evidence.empty());
    
    // Test not_verified
    VerificationResult vn = VerificationResult::not_verified("not checked");
    assert(vn.status == VerificationStatus::kNotVerified);
    
    // Test verification_failed
    VerificationResult vf = VerificationResult::verification_failed(e);
    assert(vf.status == VerificationStatus::kVerificationFailed);
    
    // Test unknown
    VerificationResult vu = VerificationResult::unknown("timeouts");
    assert(vu.status == VerificationStatus::kUnknown);
}

void test_evidence_creation() {
    Evidence e1{"procfs", "content", "2024-01-01T00:00:00Z"};
    assert(e1.source == "procfs");
    assert(e1.value == "content");
    
    // Test helper functions
    Evidence e2 = make_evidence("systemd", "active", "2024-01-01T00:00:00Z");
    assert(e2.source == "systemd");
}

void test_execution_result_with_value() {
    // Test success with value
    ExecutionResult<int> r = ExecutionResult<int>::success(42);
    assert(r.outcome == SemanticStatus::kSuccess);
    assert(r.has_value());
    assert(r.value == 42);
    assert(r.verification_successful);
    
    // Test completed (not verified)
    ExecutionResult<std::string> rc = ExecutionResult<std::string>::completed("done");
    assert(rc.outcome == SemanticStatus::kCompleted);
    assert(!rc.verification_successful);
}

void test_execution_result_void() {
    // Test success void
    ExecutionResult<void> r = ExecutionResult<void>::success();
    assert(r.outcome == SemanticStatus::kSuccess);
    assert(r.verification_successful);
    
    // Test completed void
    ExecutionResult<void> rc = ExecutionResult<void>::completed_void();
    assert(rc.outcome == SemanticStatus::kCompleted);
    assert(!rc.verification_successful);
}

void test_retry_aggregation() {
    // Create retry attempts with different results
    RetryAttempt a1;
    a1.attempt_number = 1;
    a1.execution_id = "exec-001";
    
    RetryAttempt a2;
    a2.attempt_number = 2;
    a2.execution_id = "exec-001";  // same execution, different attempt
    
    std::vector<RetryAttempt> attempts = {a1, a2};
    
    RetryAggregation ra;
    ra.attempts = attempts;
    ra.first_attempt_at = std::chrono::system_clock::now();
    ra.last_attempt_at = std::chrono::system_clock::now();
    ra.final_outcome = SemanticStatus::kSuccess;
    
    assert(ra.total_attempts() == 2);
    assert(ra.succeeded());
}

void test_helper_predicates() {
    ExecutionOutcome success = ExecutionOutcome::success();
    ExecutionOutcome failure = ExecutionOutcome::failure();
    
    assert(is_verified_success(success));
    assert(!is_verified_success(failure));
    
    assert(is_completed(success));
    assert(!is_failure(success));  // success is not a failure
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 0.17 Result/Outcome/Error model tests...\n";
    
    test_semantic_status();
    test_verification_status();
    test_execution_outcome();
    test_verification_result();
    test_evidence_creation();
    test_execution_result_with_value();
    test_execution_result_void();
    test_retry_aggregation();
    test_helper_predicates();
    
    std::cout << "All tests PASSED!\n";
    return 0;
}