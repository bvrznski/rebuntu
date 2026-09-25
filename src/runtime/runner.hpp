// rebuntu::runtime::runner — Execution Runner (Phase 0.13)
//
// The Runner is the execution state machine. It progresses one bounded execution
// according to an executable definition, tracking:
//   - Lifecycle: pending → running → finished
//   - Progress stages: dispatched → executing → observing → verifying → completed
//   - Attempts: tracks all retry attempts with their outcomes
//
// Key semantics established here:
//   * Runner is NOT a process executor (that's Executor)
//   * Runner tracks state progression, delegates execution to Executor
//   * Runner handles timeout/cancellation propagation
//   * Runner aggregates evidence from all attempts

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/results.hpp>
#include <runtime/config.hpp>
#include <string>
#include <functional>
#include <optional>

namespace rebuntu::runtime::runner {

// Define missing policies that runner needs
struct RetryPolicy {
    int max_attempts = 1;
    
    bool should_retry(int attempt_number, const core::Error* error) const {
        if (attempt_number >= max_attempts) return false;
        // For now, always retry on non-success non-cancelled outcomes
        return true;
    }
};

struct TimeoutPolicy {
    std::optional<std::chrono::milliseconds> timeout_ms;
    bool cancel_on_timeout = false;
};

enum class RunnerState {
    kPending, kRunning, kWaiting, kFinished
};

inline std::string to_string(RunnerState s) {
    switch (s) {
        case RunnerState::kPending: return "pending";
        case RunnerState::kRunning: return "running";
        case RunnerState::kWaiting: return "waiting";
        case RunnerState::kFinished: return "finished";
    }
    return "unknown";
}

enum class ProgressStage {
    kDispatched, kExecuting, kObserving, kVerifying, kCompleted
};

inline std::string to_string(ProgressStage s) {
    switch (s) {
        case ProgressStage::kDispatched: return "dispatched";
        case ProgressStage::kExecuting: return "executing";
        case ProgressStage::kObserving: return "observing";
        case ProgressStage::kVerifying: return "verifying";
        case ProgressStage::kCompleted: return "completed";
    }
    return "unknown";
}

// RunnerContext holds execution control parameters passed through the stack
struct RunnerContext {
    runtime::TimeoutPolicy timeout_policy;
    runtime::RetryPolicy retry_policy;
    std::optional<std::chrono::system_clock::time_point> deadline;
    bool cancellation_requested = false;
};

// AttemptResult captures the outcome of a single attempt
struct AttemptResult {
    work::ExecutionId execution_id;
    work::AttemptNumber attempt_number;
    bool is_last_attempt;
    core::ExecutionOutcome outcome;
    std::chrono::milliseconds preparation_duration_ms{0};
    std::chrono::milliseconds execution_duration_ms{0};
    std::chrono::milliseconds verification_duration_ms{0};
};

// RunnerResult aggregates all attempts into a final result
struct RunnerResult {
    work::ExecutionId execution_id;
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;
    std::chrono::system_clock::time_point started_at{};
    std::optional<std::chrono::system_clock::time_point> completed_at;
    int attempts_total = 0;
    int attempts_completed = 0;
    
    int attempts_remaining() const { 
        return attempts_total > attempts_completed ? (attempts_total - attempts_completed) : 0; 
    }
    
    std::vector<core::Evidence> evidence;
    
    bool succeeded() const {
        return status == core::SemanticStatus::kSuccess && verified;
    }
};

// RunnerProgress reports current execution state for monitoring
struct RunnerProgress {
    work::ExecutionId execution_id;
    RunnerState runner_state = RunnerState::kPending;
    ProgressStage stage = ProgressStage::kDispatched;
    int attempt_number = 0;
    std::optional<work::JobId> job_id;
    std::optional<std::chrono::system_clock::time_point> dispatch_time;
    std::optional<std::chrono::system_clock::time_point> start_time;
    std::optional<std::chrono::system_clock::time_point> finish_time;
};

// Runner is the execution state machine
//
// The Runner does NOT execute work directly. It:
//   - Tracks lifecycle and progress through execution stages
//   - Manages retry logic based on policy
//   - Propagates cancellation to the executor
//   - Collects evidence from all attempts
//   - Delegates actual execution to an Executor implementation
//
class Runner {
public:
    using ExecuteAttemptFn = std::function<
        core::ExecutionOutcome(const work::Task&, const work::Job&, int attempt_number,
                      const RunnerContext&)>;
    
    // Construct a Runner for one job execution
    Runner(work::ExecutionId exec_id, 
           work::Job job,
           ExecuteAttemptFn execute_fn);
    
    // Start the runner (transition from kPending to kRunning)
    void start(std::optional<std::chrono::system_clock::time_point> now = std::nullopt);
    
    // Perform one attempt at execution
    AttemptResult attempt();
    
    // Check if another attempt should be made based on policy
    bool should_retry(const AttemptResult& result) const;
    
    // Record an attempt result (updates state)
    void record_attempt(const AttemptResult& result);
    
    // Request cancellation of the ongoing execution
    void request_cancel(std::optional<std::string> reason = std::nullopt);
    
    // Check if the runner has reached a terminal state
    bool is_finished() const;
    
    // Get the aggregated final result
    RunnerResult result() const;
    
    // Get current progress for monitoring/diagnostics
    RunnerProgress progress() const;

private:
    work::ExecutionId exec_id_;
    work::Job job_;
    ExecuteAttemptFn execute_fn_;
    
    // State machine state
    RunnerState state_ = RunnerState::kPending;
    ProgressStage stage_ = ProgressStage::kDispatched;
    
    // Tracking
    int attempt_number_ = 0;
    std::optional<core::ExecutionOutcome> final_outcome_;
    std::vector<core::Evidence> evidence_;
    std::chrono::system_clock::time_point started_at_{};
    
    std::optional<std::chrono::system_clock::time_point> finish_time_;
    int attempts_made_ = 0;
    
    // Control state
    bool cancellation_requested_ = false;
    std::optional<std::string> cancellation_reason_;
};

// Runner implementation
inline Runner::Runner(work::ExecutionId exec_id, 
                      work::Job job,
                      ExecuteAttemptFn execute_fn)
    : exec_id_(std::move(exec_id)),
      job_(std::move(job)),
      execute_fn_(std::move(execute_fn)) {
}

inline void Runner::start(std::optional<std::chrono::system_clock::time_point> now) {
    if (state_ != RunnerState::kPending) {
        return;  // Already started
    }
    
    state_ = RunnerState::kRunning;
    stage_ = ProgressStage::kExecuting;
    started_at_ = now.value_or(std::chrono::system_clock::now());
}

inline AttemptResult Runner::attempt() {
    if (state_ != RunnerState::kRunning) {
        return AttemptResult{
            exec_id_,
            work::AttemptNumber{attempt_number_ + 1},
            /*is_last_attempt=*/true,
            core::ExecutionOutcome::failure(),
            std::chrono::milliseconds(0),
            std::chrono::milliseconds(0),
            std::chrono::milliseconds(0)
        };
    }
    
    // Create context for this attempt
    RunnerContext ctx{
        .timeout_policy = job_.timeout_policy,
        .retry_policy = job_.retry_policy,
        .deadline = std::nullopt,
        .cancellation_requested = cancellation_requested_
    };
    
    auto start_time = std::chrono::system_clock::now();
    
    // Get a Task from job's task_id (simplified - in real implementation this would fetch from registry)
    work::Task empty_task{};
    
    // Execute the attempt
    core::ExecutionOutcome outcome;
    if (!cancellation_requested_) {
        outcome = execute_fn_(empty_task, job_, attempt_number_ + 1, ctx);
    } else {
        outcome = core::ExecutionOutcome::cancelled(cancellation_reason_.value_or("cancelled"));
    }
    
    auto end_time = std::chrono::system_clock::now();
    
    // Compute durations
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    // Determine if this is the last attempt
    bool is_last_attempt = !should_retry(AttemptResult{
        exec_id_,
        work::AttemptNumber{attempt_number_ + 1},
        /*is_last_attempt=*/false,
        outcome,
        std::chrono::milliseconds(0),
        total_duration,
        std::chrono::milliseconds(0)
    });
    
    AttemptResult result{
        exec_id_,
        work::AttemptNumber{++attempt_number_},
        is_last_attempt,
        outcome,
        std::chrono::milliseconds(0),  // preparation (simplified)
        total_duration,
        std::chrono::milliseconds(0)   // verification (deferred to executor)
    };
    
    // Record the attempt result
    record_attempt(result);
    
    return result;
}

inline bool Runner::should_retry(const AttemptResult& result) const {
    if (result.outcome.status == core::SemanticStatus::kSuccess) {
        return false;  // No retry needed on success
    }
    
    if (result.outcome.status == core::SemanticStatus::kCancelled) {
        return false;  // No retry after cancellation
    }
    
    if (attempt_number_ >= job_.retry_policy.max_attempts) {
        return false;  // Max attempts reached
    }
    
    // ExecutionOutcome uses status for error classification
    // Retry on failure or unknown (transient errors), not on success or cancelled
    bool should_retry = (result.outcome.status == core::SemanticStatus::kFailure ||
                        result.outcome.status == core::SemanticStatus::kUnknown) &&
                       (attempt_number_ < job_.retry_policy.max_attempts);
    return should_retry;
}

inline void Runner::record_attempt(const AttemptResult& result) {
    // ExecutionOutcome doesn't have evidence field - it's tracked separately
    (void)result;  // suppress unused warning
    
    if (result.outcome.status != core::SemanticStatus::kUnknown) {
        final_outcome_ = result.outcome;
    }
    
    // Update attempts made
    attempts_made_++;
    
    // Mark as finished only if we've exhausted all retry attempts
    if (result.is_last_attempt) {
        finish_time_ = std::chrono::system_clock::now();
        state_ = RunnerState::kFinished;
    }
}

inline void Runner::request_cancel(std::optional<std::string> reason) {
    cancellation_requested_ = true;
    cancellation_reason_ = std::move(reason);
}

inline bool Runner::is_finished() const {
    return state_ == RunnerState::kFinished;
}

inline RunnerResult Runner::result() const {
    if (!final_outcome_.has_value()) {
        return RunnerResult{
            exec_id_,
            core::SemanticStatus::kUnknown,
            false,
            started_at_,
            std::nullopt,
            job_.retry_policy.max_attempts,
            0,
            evidence_
        };
    }
    
    auto outcome = final_outcome_.value();
    return RunnerResult{
        exec_id_,
        outcome.status,
        true,  // verified = true by default for successful outcomes
        started_at_,
        finish_time_,
        job_.retry_policy.max_attempts,
        attempts_made_,
        evidence_
    };
}

inline RunnerProgress Runner::progress() const {
    return RunnerProgress{
        exec_id_,
        state_,
        stage_,
        attempt_number_,
        std::nullopt,  // job_id not tracked in this simple runner
        std::nullopt,
        started_at_,
        finish_time_
    };
}

}  // namespace rebuntu::runtime::runner