// rebuntu::runtime::runner — Execution Runner (Phase 0.13, Phase 6.21)
//
// The Runner is the execution state machine
// Verification is a SEPARATE stage from execution:
//   - EXECUTION: runs the operation/provider
//   - VERIFICATION: checks if postconditions hold after execution

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/results.hpp>
#include <optional>
#include <chrono>
#include <string>
#include <functional>
#include <memory>

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

// Verification result from a single verification check
struct AttemptVerificationResult {
    core::VerificationStatus status = core::VerificationStatus::kNotVerified;
    std::chrono::milliseconds duration_ms{0};
    std::vector<Evidence> evidence;
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
    
    // Verify the execution result against postconditions
    // Only meaningful after at least one attempt has been made
    AttemptVerificationResult verify();
    
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

std::unique_ptr<Runner> make_runner(
    ExecutionId exec_id,
    Job job,
    Runner::ExecuteAttemptFn execute_fn);

}  // namespace rebuntu::runtime::runner