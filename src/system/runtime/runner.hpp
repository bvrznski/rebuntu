// rebuntu::runtime::runner — Execution Runner (Phase 0.13)
#pragma once

#include <system/runtime/work.hpp>
#include <system/core/contracts.hpp>
#include <string>
#include <functional>
#include <optional>

namespace rebuntu::runtime::runner {

enum class RunnerState {
    kPending, kRunning, kWaiting, kFinished
};

enum class ProgressStage {
    kDispatched, kExecuting, kObserving, kVerifying, kCompleted
};

inline std::string_view to_string(RunnerState s) {
    switch (s) {
        case RunnerState::kPending: return "pending";
        case RunnerState::kRunning: return "running";
        case RunnerState::kWaiting: return "waiting";
        case RunnerState::kFinished: return "finished";
    }
    return "unknown";
}

inline std::string_view to_string(ProgressStage s) {
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
    runtime::TimeoutPolicy timeout_policy;
    runtime::RetryPolicy retry_policy;
    std::optional<std::chrono::system_clock::time_point> deadline;
    bool cancellation_requested = false;
};

struct AttemptResult {
    work::ExecutionId execution_id;
    work::AttemptNumber attempt_number;
    bool is_last_attempt;
    core::Outcome outcome;
    std::chrono::milliseconds preparation_duration_ms{0};
    std::chrono::milliseconds execution_duration_ms{0};
    std::chrono::milliseconds verification_duration_ms{0};
};

struct RunnerResult {
    work::ExecutionId execution_id;
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;
    std::chrono::system_clock::time_point started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    int attempts_total = 0;
    int attempts_completed = 0;
    int attempts_remaining() const { return attempts_total - attempts_completed; }
    std::vector<core::Evidence> evidence;
    bool succeeded() const {
        return status == core::SemanticStatus::kSuccess && verified;
    }
};

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

class Runner {
public:
    using ExecuteAttemptFn = std::function<
        core::Outcome(const work::Task&, const work::Job&, int attempt_number)>;
    
    Runner(work::ExecutionId exec_id, 
           work::Job job,
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
    work::ExecutionId exec_id_;
    work::Job job_;
    ExecuteAttemptFn execute_fn_;
    
    RunnerState state_ = RunnerState::kPending;
    ProgressStage stage_ = ProgressStage::kDispatched;
    int attempt_number_ = 0;
    std::optional<core::Outcome> final_outcome_;
    std::vector<core::Evidence> evidence_;
    std::optional<std::chrono::system_clock::time_point> start_time_;
    std::optional<std::chrono::system_clock::time_point> finish_time_;
    int attempts_made_ = 0;
    bool cancellation_requested_ = false;
    std::optional<std::string> cancellation_reason_;
};

}  // namespace rebuntu::runtime::runner
