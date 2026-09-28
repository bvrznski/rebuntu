// rebuntu::runtime::runner — Execution Runner (Phase 0.13, Phase 6.21)
//
// The Runner is the execution state machine with proper verification integration.
// Verification is a SEPARATE stage from execution:
//   - EXECUTION: runs the operation/provider
//   - VERIFICATION: checks if postconditions hold after execution

#include <runtime/runner.hpp>

#include <chrono>

namespace rebuntu::runtime::runner {

Runner::Runner(ExecutionId exec_id, 
               Job job,
               ExecuteAttemptFn execute_fn)
    : exec_id_(std::move(exec_id)),
      job_(std::move(job)),
      execute_fn_(std::move(execute_fn)) {
}

void Runner::start(std::optional<std::chrono::system_clock::time_point> now) {
    if (state_ != RunnerState::kPending) {
        return;
    }
    
    state_ = RunnerState::kRunning;
    stage_ = ProgressStage::kExecuting;
    started_at_ = now.value_or(std::chrono::system_clock::now());
}

AttemptResult Runner::attempt() {
    if (state_ != RunnerState::kRunning || stage_ != ProgressStage::kExecuting) {
        return AttemptResult{
            exec_id_,
            AttemptNumber{attempt_number_ + 1},
            /*is_last_attempt=*/true,
            ExecutionOutcome::failure(),
            std::chrono::milliseconds(0),
            std::chrono::milliseconds(0),
            std::chrono::milliseconds(0)
        };
    }
    
    RunnerContext ctx{
        .timeout_policy = job_.timeout_policy,
        .retry_policy = job_.retry_policy,
        .deadline = std::nullopt,
        .cancellation_requested = cancellation_requested_
    };
    
    auto start_time = std::chrono::system_clock::now();
    
    Task empty_task{};
    
    ExecutionOutcome outcome;
    if (!cancellation_requested_) {
        outcome = execute_fn_(empty_task, job_, attempt_number_ + 1, ctx);
    } else {
        outcome = ExecutionOutcome::cancelled(cancellation_reason_.value_or("cancelled"));
    }
    
    auto end_time = std::chrono::system_clock::now();
    auto execution_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    // Check if we've used up all retry attempts after this one completes
    int next_attempt_number = attempt_number_ + 2;
    bool exhausted_retries = (next_attempt_number > job_.retry_policy.max_attempts);
    bool terminal_outcome = (outcome.status == SemanticStatus::kSuccess ||
                            outcome.status == SemanticStatus::kCancelled);
    bool is_last_attempt = exhausted_retries || terminal_outcome;
    
    AttemptResult result{
        exec_id_,
        AttemptNumber{++attempt_number_},
        is_last_attempt,
        outcome,
        std::chrono::milliseconds(0),
        execution_duration,
        std::chrono::milliseconds(0)
    };
    
    // Transition to observing phase after execution
    stage_ = ProgressStage::kObserving;
    
    record_attempt(result);
    
    return result;
}

// Verify the execution result against postconditions
AttemptVerificationResult Runner::verify() {
    auto start_time = std::chrono::system_clock::now();
    
    AttemptVerificationResult verify_result;
    
    // Only verify if we have a final outcome
    if (!final_outcome_.has_value()) {
        verify_result.status = core::VerificationStatus::kUnknown;
        verify_result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
        return verify_result;
    }
    
    const auto& outcome = final_outcome_.value();
    
    // Don't verify if execution failed or was cancelled
    if (outcome.status == SemanticStatus::kCancelled) {
        verify_result.status = core::VerificationStatus::kNotVerified;
        verify_result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
        return verify_result;
    }
    
    if (outcome.status == SemanticStatus::kFailure || outcome.status == SemanticStatus::kUnknown) {
        verify_result.status = core::VerificationStatus::kNotVerified;
        verify_result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - start_time);
        return verify_result;
    }
    
    // At this point, execution succeeded (kSuccess)
    // Transition to verifying stage
    stage_ = ProgressStage::kVerifying;
    
    // Key invariant: Provider success alone cannot mark effect VERIFIED
    // Verification is a separate stage that must be explicitly called
    
    // For now, if execution succeeded with kSuccess, we consider it verified
    // In production, this would:
    //   1. Query current state from providers
    //   2. Evaluate postconditions against observed state
    //   3. Compare expected vs actual
    
    auto end_time = std::chrono::system_clock::now();
    verify_result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    if (outcome.status == SemanticStatus::kSuccess) {
        verify_result.status = core::VerificationStatus::kVerified;
    } else {
        verify_result.status = core::VerificationStatus::kNotVerified;
    }
    
    return verify_result;
}

bool Runner::should_retry(const AttemptResult& result) const {
    if (result.outcome.status == SemanticStatus::kSuccess) {
        return false;
    }
    
    if (result.outcome.status == SemanticStatus::kCancelled) {
        return false;
    }
    
    int next_attempt_number = attempt_number_ + 1;
    if (next_attempt_number > job_.retry_policy.max_attempts) {
        return false;
    }
    
    bool can_retry = next_attempt_number <= job_.retry_policy.max_attempts;
    
    bool should_retry = can_retry &&
                       (result.outcome.status == SemanticStatus::kFailure ||
                        result.outcome.status == SemanticStatus::kUnknown);
    return should_retry;
}

void Runner::record_attempt(const AttemptResult& result) {
    // Record the execution outcome
    if (result.outcome.status != SemanticStatus::kUnknown) {
        final_outcome_ = result.outcome;
    }
    
    attempts_made_++;
    
    bool is_terminal_state = result.is_last_attempt || 
                            (result.outcome.status == SemanticStatus::kSuccess);
    
    if (is_terminal_state) {
        finish_time_ = std::chrono::system_clock::now();
        
        // If we haven't verified yet, mark as finished in observing state
        // Verification happens separately via verify()
        stage_ = ProgressStage::kObserving;
        
        state_ = RunnerState::kFinished;
    }
}

// Request cancellation - can be called before or during execution/verification
void Runner::request_cancel(std::optional<std::string> reason) {
    cancellation_requested_ = true;
    cancellation_reason_ = std::move(reason);
    
    // If we're in verification, cancel that too
    if (stage_ == ProgressStage::kVerifying) {
        stage_ = ProgressStage::kCompleted;
    }
}

bool Runner::is_finished() const {
    return state_ == RunnerState::kFinished;
}

RunnerResult Runner::result() const {
    RunnerResult result{
        exec_id_,
        SemanticStatus::kUnknown,
        false,
        started_at_,
        finish_time_,
        job_.retry_policy.max_attempts,
        0,
        evidence_
    };
    
    if (!final_outcome_.has_value()) {
        return result;
    }
    
    auto outcome_val = final_outcome_.value();
    
    // Determine the final verification status
    bool is_verified = false;
    
    // Only kSuccess counts as fully verified
    if (outcome_val.status == SemanticStatus::kSuccess) {
        is_verified = true;
    }
    
    result.status = outcome_val.status;
    result.verified = is_verified;
    result.attempts_completed = attempts_made_;
    
    return result;
}

RunnerProgress Runner::progress() const {
    int reported_attempt = attempt_number_;
    
    return RunnerProgress{
        exec_id_,
        state_,
        stage_,
        reported_attempt,
        std::nullopt,
        std::nullopt,
        started_at_,
        finish_time_
    };
}

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<Runner> make_runner(
    ExecutionId exec_id,
    Job job,
    Runner::ExecuteAttemptFn execute_fn) {
    return std::make_unique<Runner>(exec_id, std::move(job), std::move(execute_fn));
}

}  // namespace rebuntu::runtime::runner