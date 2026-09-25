// rebuntu::runtime::runner — Execution Runner (Phase 0.13)
//
// The Runner is the execution state machine

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/results.hpp>
#include <optional>
#include <chrono>
#include <string>
#include <functional>

namespace rebuntu::runtime::runner {

// Bring work namespace types into scope
using TimeoutPolicy = rebuntu::runtime::work::TimeoutPolicy;
using RetryPolicy = rebuntu::runtime::work::RetryPolicy;
using ExecutionId = rebuntu::runtime::work::ExecutionId;
using AttemptNumber = rebuntu::runtime::work::AttemptNumber;
using JobId = rebuntu::runtime::work::JobId;
using Task = rebuntu::runtime::work::Task;
using Job = rebuntu::runtime::work::Job;

// Bring core types into scope
using ExecutionOutcome = rebuntu::core::ExecutionOutcome;
using SemanticStatus = rebuntu::core::SemanticStatus;
using Evidence = rebuntu::core::Evidence;

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

struct RunnerContext {
    TimeoutPolicy timeout_policy;
    RetryPolicy retry_policy;
    std::optional<std::chrono::system_clock::time_point> deadline;
    bool cancellation_requested = false;
};

struct AttemptResult {
    ExecutionId execution_id;
    AttemptNumber attempt_number;
    bool is_last_attempt;
    ExecutionOutcome outcome;
    std::chrono::milliseconds preparation_duration_ms{0};
    std::chrono::milliseconds execution_duration_ms{0};
    std::chrono::milliseconds verification_duration_ms{0};
};

struct RunnerResult {
    ExecutionId execution_id;
    SemanticStatus status = SemanticStatus::kUnknown;
    bool verified = false;
    std::chrono::system_clock::time_point started_at{};
    std::optional<std::chrono::system_clock::time_point> completed_at;
    int attempts_total = 0;
    int attempts_completed = 0;
    
    int attempts_remaining() const { 
        return attempts_total > attempts_completed ? (attempts_total - attempts_completed) : 0; 
    }
    
    std::vector<Evidence> evidence;
    
    bool succeeded() const {
        return status == SemanticStatus::kSuccess && verified;
    }
};

struct RunnerProgress {
    ExecutionId execution_id;
    RunnerState runner_state = RunnerState::kPending;
    ProgressStage stage = ProgressStage::kDispatched;
    int attempt_number = 0;
    std::optional<JobId> job_id;
    std::optional<std::chrono::system_clock::time_point> dispatch_time;
    std::optional<std::chrono::system_clock::time_point> start_time;
    std::optional<std::chrono::system_clock::time_point> finish_time;
};

class Runner {
public:
    using ExecuteAttemptFn = std::function<
        ExecutionOutcome(const Task&, const Job&, int attempt_number,
                      const RunnerContext&)>;
    
    Runner(ExecutionId exec_id, 
           Job job,
           ExecuteAttemptFn execute_fn);
    
    void start(std::optional<std::chrono::system_clock::time_point> now = std::nullopt);
    
    AttemptResult attempt();
    
    bool should_retry(const AttemptResult& result) const;
    
    void record_attempt(const AttemptResult& result);
    
    void request_cancel(std::optional<std::string> reason = std::nullopt);
    
    bool is_finished() const;
    
    RunnerResult result() const;
    
    RunnerProgress progress() const;

private:
    ExecutionId exec_id_;
    Job job_;
    ExecuteAttemptFn execute_fn_;
    
    RunnerState state_ = RunnerState::kPending;
    ProgressStage stage_ = ProgressStage::kDispatched;
    
    int attempt_number_ = 0;
    std::optional<ExecutionOutcome> final_outcome_;
    std::vector<Evidence> evidence_;
    std::chrono::system_clock::time_point started_at_{};
    
    std::optional<std::chrono::system_clock::time_point> finish_time_;
    int attempts_made_ = 0;
    
    bool cancellation_requested_ = false;
    std::optional<std::string> cancellation_reason_;
};

inline Runner::Runner(ExecutionId exec_id, 
                      Job job,
                      ExecuteAttemptFn execute_fn)
    : exec_id_(std::move(exec_id)),
      job_(std::move(job)),
      execute_fn_(std::move(execute_fn)) {
}

inline void Runner::start(std::optional<std::chrono::system_clock::time_point> now) {
    if (state_ != RunnerState::kPending) {
        return;
    }
    
    state_ = RunnerState::kRunning;
    stage_ = ProgressStage::kExecuting;
    started_at_ = now.value_or(std::chrono::system_clock::now());
}

inline AttemptResult Runner::attempt() {
    if (state_ != RunnerState::kRunning) {
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
    
    auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    // Check if we've used up all retry attempts after this one completes
    // This is the LAST allowed attempt if: current + 1 > max
    int next_attempt_number = attempt_number_ + 2;  // What would be the NEXT attempt number
    bool exhausted_retries = (next_attempt_number > job_.retry_policy.max_attempts);
    bool terminal_outcome = (outcome.status == SemanticStatus::kSuccess ||
                            outcome.status == SemanticStatus::kCancelled);
    bool is_last_attempt = exhausted_retries || terminal_outcome;
    
    // Record attempt number (before increment, for progress reporting)
    int current_attempt = attempt_number_;
    
    AttemptResult result{
        exec_id_,
        AttemptNumber{++attempt_number_},
        is_last_attempt,
        outcome,
        std::chrono::milliseconds(0),
        total_duration,
        std::chrono::milliseconds(0)
    };
    
    record_attempt(result);
    
    return result;
}

inline bool Runner::should_retry(const AttemptResult& result) const {
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

inline void Runner::record_attempt(const AttemptResult& result) {
    (void)result;
    
    if (result.outcome.status != SemanticStatus::kUnknown) {
        final_outcome_ = result.outcome;
    }
    
    attempts_made_++;
    
    bool is_terminal_state = result.is_last_attempt || 
                            (result.outcome.status == SemanticStatus::kSuccess);
    
    if (is_terminal_state) {
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
            SemanticStatus::kUnknown,
            false,
            started_at_,
            std::nullopt,
            job_.retry_policy.max_attempts,
            0,
            evidence_
        };
    }
    
    auto outcome_val = final_outcome_.value();
    return RunnerResult{
        exec_id_,
        outcome_val.status,
        true,
        started_at_,
        finish_time_,
        job_.retry_policy.max_attempts,
        attempts_made_,
        evidence_
    };
}

inline RunnerProgress Runner::progress() const {
    // Report the last completed attempt number (attempt_number_ has already been incremented)
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

}  // namespace rebuntu::runtime::runner