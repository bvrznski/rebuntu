// rebuntu::runtime::runner — Execution Runner implementation (Phase 4.4)
//
// The Runner manages the lifecycle state machine of an execution:
//   - Lifecycle states: pending, running, waiting, finished
//   - Progress stages: dispatched, executing, observing, verifying, completed
//   - Retry management with exponential backoff
//   - Cancellation handling
//   - Attempt history tracking
//
// The Runner is NOT responsible for:
//   - Native execution (delegates to execute_fn_ which wraps Executor)
//   - Policy decisions (authorization, scheduling)
//   - State persistence (unless explicitly configured)

#include <system/runtime/runner.hpp>

#include <chrono>
#include <optional>
#include <string>

namespace rebuntu::runtime::runner {

Runner::Runner(work::ExecutionId exec_id,
               work::Job job,
               ExecuteAttemptFn execute_fn)
    : exec_id_(std::move(exec_id)),
      job_(std::move(job)),
      execute_fn_(std::move(execute_fn)) {
}

void Runner::start(std::optional<std::chrono::system_clock::time_point> now) {
    if (state_ != RunnerState::kPending) {
        return;  // Already started or finished
    }
    
    state_ = RunnerState::kRunning;
    stage_ = ProgressStage::kExecuting;
    start_time_ = now.value_or(std::chrono::system_clock::now());
}

AttemptResult Runner::attempt() {
    if (state_ != RunnerState::kRunning) {
        // Return a placeholder result for invalid state
        AttemptResult result;
        result.execution_id = exec_id_;
        result.attempt_number = work::AttemptNumber{attempt_number_ + 1};
        result.is_last_attempt = true;
        result.outcome = core::Outcome::failure("E_RUNNER_STATE", "Runner not in running state");
        return result;
    }
    
    attempt_number_++;
    stage_ = ProgressStage::kExecuting;
    
    auto start_exec = std::chrono::steady_clock::now();
    
    // Execute the attempt via the provided function
    core::Outcome outcome = execute_fn_(work::Task{}, job_, attempt_number_);
    
    auto end_exec = std::chrono::steady_clock::now();
    auto exec_duration = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end_exec - start_exec);
    
    AttemptResult result;
    result.execution_id = exec_id_;
    result.attempt_number = work::AttemptNumber{attempt_number_};
    result.is_last_attempt = !should_retry(result);
    result.outcome = outcome;
    result.execution_duration_ms = exec_duration;
    
    // Record the attempt
    record_attempt(result);
    
    return result;
}

bool Runner::should_retry(const AttemptResult& result) const {
    // Check if we've exceeded max attempts (default to 1)
    int max_attempts = job_.max_attempts.value_or(work::AttemptNumber{1}).value;
    if (attempt_number_ >= max_attempts) {
        return false;
    }
    
    // Check if cancellation was requested
    if (cancellation_requested_) {
        return false;
    }
    
    // Check outcome status - only retry non-success outcomes
    if (result.outcome.status == core::SemanticStatus::kSuccess) {
        return false;
    }
    
    // For other statuses, check if they're retryable based on policy
    // The job_.retry_policy determines retry behavior
    
    return true;
}

void Runner::record_attempt(const AttemptResult& result) {
    // Update progress stage
    stage_ = ProgressStage::kVerifying;
    
    // Record the outcome
    final_outcome_ = result.outcome;
    attempts_made_++;
    
    // Check if we should mark as finished
    bool is_last = !should_retry(result);
    if (is_last || result.outcome.status == core::SemanticStatus::kSuccess) {
        finish_time_ = std::chrono::system_clock::now();
        
        if (result.outcome.status == core::SemanticStatus::kSuccess) {
            state_ = RunnerState::kFinished;
        } else if (cancellation_requested_) {
            state_ = RunnerState::kWaiting;
        } else {
            state_ = RunnerState::kFinished;
        }
    }
}

void Runner::request_cancel(std::optional<std::string> reason) {
    cancellation_requested_ = true;
    cancellation_reason_ = std::move(reason);
    
    // If already finished, don't change state
    if (state_ == RunnerState::kFinished) {
        return;
    }
    
    // Mark as waiting to indicate cancelled
    if (state_ == RunnerState::kRunning) {
        state_ = RunnerState::kWaiting;
    }
}

bool Runner::is_finished() const {
    return state_ == RunnerState::kFinished;
}

RunnerResult Runner::result() const {
    RunnerResult r;
    r.execution_id = exec_id_;
    r.status = final_outcome_.has_value() 
        ? final_outcome_->status 
        : core::SemanticStatus::kUnknown;
    r.verified = final_outcome_.has_value() && final_outcome_->verified;
    r.started_at = start_time_.value_or(std::chrono::system_clock::now());
    
    if (finish_time_) {
        r.completed_at = finish_time_;
    }
    
    // Get max attempts from job
    int max_attempts = job_.max_attempts.value_or(work::AttemptNumber{1}).value;
    r.attempts_total = max_attempts;
    r.attempts_completed = attempts_made_;
    
    // Collect evidence from the outcome
    if (final_outcome_) {
        r.evidence = final_outcome_->evidence;
    }
    
    return r;
}

RunnerProgress Runner::progress() const {
    RunnerProgress p;
    p.execution_id = exec_id_;
    p.runner_state = state_;
    p.stage = stage_;
    p.attempt_number = attempt_number_;
    p.job_id = work::JobId{job_.id.value};
    p.dispatch_time = start_time_;
    p.start_time = start_time_;
    
    if (finish_time_) {
        p.finish_time = finish_time_;
    }
    
    return p;
}

}  // namespace rebuntu::runtime::runner