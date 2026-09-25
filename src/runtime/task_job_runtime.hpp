// rebuntu::runtime::task_job_runtime — Task/Job Runtime (Phase 4.13)
//
// This file establishes Rebuntu's Task/Job execution runtime:
//   - Task = bounded requested work (specification)
//   - Job = concrete submitted/managed realization (instance)
//   - Execution = runtime occurrence of a job
//   - Attempt = one try within an execution
//
// Key semantics established here:
//   * TASK != JOB != EXECUTION != ATTEMPT
//   * EXECUTED != VERIFIED
//   * RETRY CREATES A NEW ATTEMPT; IT DOES NOT ERASE HISTORY

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/work.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/subprocess_executor.hpp>
#include <runtime/runner.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace rebuntu::runtime {

// ============================================================================
// JobExecutionState
// Lifecycle state of a job's execution instance
// ============================================================================

enum class JobExecutionState {
    kCreated,        // job record created
    kQueued,         // waiting for resources/queue slot
    kDispatched,     // dispatched to executor
    kRunning,        // execution in progress
    kCompleted,      // all attempts completed (success or exhausted)
    kCancelled,      // explicitly cancelled
    kTimedOut,       // execution timed out
};

inline std::string to_string(JobExecutionState s) {
    switch (s) {
        case JobExecutionState::kCreated:     return "created";
        case JobExecutionState::kQueued:      return "queued";
        case JobExecutionState::kDispatched:  return "dispatched";
        case JobExecutionState::kRunning:     return "running";
        case JobExecutionState::kCompleted:   return "completed";
        case JobExecutionState::kCancelled:   return "cancelled";
        case JobExecutionState::kTimedOut:    return "timed_out";
    }
    return "unknown";
}

// ============================================================================
// AttemptOutcome
// Result of one attempt in a job execution
//
// Retries create NEW attempts; they do not erase history.
// ============================================================================

struct AttemptOutcome {
    work::AttemptNumber number;
    
    // Timing
    std::chrono::system_clock::time_point started_at{};
    std::optional<std::chrono::system_clock::time_point> finished_at;
    
    // Outcome
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;
    
    // Execution details
    int32_t pid = 0;
    int exit_code = 0;
    std::optional<std::string> signal_name;  // if terminated by signal
    
    // Output capture (bounded)
    std::optional<std::string> stdout_data;
    std::optional<std::string> stderr_data;
    
    // Error info (if failed)
    core::Error* error = nullptr;  // pointer to owning result's error
};

// ============================================================================
// ExecutionHistory
// Complete history of all attempts in a job execution
//
// This preserves attempt history even when final outcome is success.
// ============================================================================

struct ExecutionHistory {
    std::vector<AttemptOutcome> attempts;
    
    std::chrono::system_clock::time_point first_attempt_at{};
    std::optional<std::chrono::system_clock::time_point> last_attempt_at;
    
    // Overall timing
    std::optional<std::chrono::milliseconds> total_duration_ms;
    
    bool has_successful_attempt() const {
        for (const auto& a : attempts) {
            if (a.status == core::SemanticStatus::kSuccess) {
                return true;
            }
        }
        return false;
    }
};

// ============================================================================
// JobExecutionResult
// The final result of a job execution with full attempt history
// ============================================================================

struct JobExecutionResult {
    work::JobId job_id;
    work::TaskId task_id;
    
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;  // true only if postconditions verified
    
    JobExecutionState state = JobExecutionState::kCreated;
    
    ExecutionHistory history;
    
    std::chrono::system_clock::time_point created_at{};
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
};

// ============================================================================
// JobRuntimeMetrics
// Runtime metrics for monitoring job execution
// ============================================================================

struct JobRuntimeMetrics {
    size_t jobs_submitted = 0;
    size_t jobs_completed = 0;
    size_t jobs_failed = 0;
    size_t jobs_cancelled = 0;
    size_t jobs_timed_out = 0;
    
    size_t total_attempts = 0;
    size_t successful_attempts = 0;
    size_t failed_attempts = 0;
};

// ============================================================================
// TaskJobRuntime
//
// The canonical runtime for executing Tasks as Jobs with:
//   - Attempt history preservation (no erasure on retry)
//   - Timeout enforcement via kernel timerfd
//   - Cancellation token propagation
//   - Independent verification of postconditions
// ============================================================================

class TaskJobRuntime {
public:
    // Construct with subprocess executor and optional default policies
    explicit TaskJobRuntime(
        std::unique_ptr<SubprocessExecutor> subprocess_executor,
        work::RetryPolicy default_retry_policy = {},
        work::TimeoutPolicy default_timeout_policy = {});
    
    ~TaskJobRuntime();
    
    // Submit a task for execution as a job
    JobExecutionResult submit(const work::Task& task,
                              const std::vector<std::pair<std::string, std::string>>& parameters = {},
                              int max_attempts = 1);
    
    // Cancel an in-flight execution
    bool cancel(work::JobId job_id);
    
    // Get current state of a job execution
    JobExecutionState get_state(work::JobId job_id) const;
    
    // Get full result with history for a completed execution
    std::optional<JobExecutionResult> get_result(work::JobId job_id) const;
    
    // Get runtime metrics
    JobRuntimeMetrics metrics() const;

private:
    // Execute one attempt of a task (called by run_job)
    AttemptOutcome execute_attempt(const work::Task& task,
                                   int attempt_number,
                                   CancellationToken& cancel_token);
    
    // Verify postconditions after execution completes
    bool verify_postconditions(const work::Task& task, const AttemptOutcome& outcome) const;
    
    // Execute a job (full retry loop with history)
    JobExecutionResult run_job(const work::Task& task,
                               int max_attempts,
                               CancellationToken& cancel_token);
    
    // Subprocess executor for native execution
    std::unique_ptr<SubprocessExecutor> subprocess_executor_;
    
    // Default policies (used when not specified in job submission)
    work::RetryPolicy default_retry_policy_;
    work::TimeoutPolicy default_timeout_policy_;
    
    // Execution records storage
    mutable std::mutex executions_mutex_;
    std::unordered_map<work::JobId, JobExecutionResult> executions_;
    
    // Metrics (thread-safe via mutex)
    mutable std::mutex metrics_mutex_;
    JobRuntimeMetrics metrics_;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<TaskJobRuntime> make_task_job_runtime();

}  // namespace rebuntu::runtime