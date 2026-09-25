// rebuntu::runtime::unit_executor — Unit Execution Runtime (Phase 4.11)
//
// The UnitExecutor is the runtime realization of Rebuntu Units according to
// the Phase 0.7 contract. It integrates:
//   - Task/Job/Execution state management via Runner
//   - Native execution via Executor (subprocess/systemd/dbus)
//   - Resolution via Resolver (semantic → executable mapping)
//   - Evidence production and verification

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/results.hpp>
#include <runtime/subprocess_executor.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

namespace rebuntu::runtime::unit_executor {

// ============================================================================
// UnitExecutionState
// The lifecycle state of a unit execution instance
// ============================================================================

enum class UnitExecutionState {
    kCreated,
    kQueued,
    kDispatched,
    kRunning,
    kCompleted,
    kCancelled,
};

inline std::string to_string(UnitExecutionState s) {
    switch (s) {
        case UnitExecutionState::kCreated: return "created";
        case UnitExecutionState::kQueued: return "queued";
        case UnitExecutionState::kDispatched: return "dispatched";
        case UnitExecutionState::kRunning: return "running";
        case UnitExecutionState::kCompleted: return "completed";
        case UnitExecutionState::kCancelled: return "cancelled";
    }
    return "unknown";
}

// ============================================================================
// AttemptRecord
// A single attempt within an execution
// ============================================================================

struct AttemptRecord {
    work::AttemptNumber number;
    std::chrono::system_clock::time_point started_at;
    
    core::SemanticStatus outcome_status = core::SemanticStatus::kUnknown;
    
    int32_t pid = 0;
    int exit_code = 0;
    std::string stdout_data;
    std::string stderr_data;
    
    std::chrono::milliseconds execution_duration_ms{0};
    
    bool verified = false;
    core::VerificationStatus verification_status = core::VerificationStatus::kNotVerified;
};

// ============================================================================
// ExecutionResult
// The final result of an execution (may include multiple attempts)
// ============================================================================

struct ExecutionResult {
    work::ExecutionId execution_id;
    work::JobId job_id;
    
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;
    
    UnitExecutionState state = UnitExecutionState::kCreated;
    
    std::chrono::system_clock::time_point created_at;
};

// ============================================================================
// ExecutionMetrics
// Runtime metrics for monitoring
// ============================================================================

struct ExecutionMetrics {
    size_t executions_submitted = 0;
    size_t executions_completed = 0;
    size_t executions_failed = 0;
    size_t executions_cancelled = 0;
    size_t total_attempts = 0;
    std::chrono::milliseconds total_execution_time_ms{0};
};

// ============================================================================
// UnitExecutor
// ============================================================================

class UnitExecutor {
public:
    explicit UnitExecutor();
    
    ~UnitExecutor();
    
    ExecutionResult submit(const work::Task& task, 
                           const std::vector<std::pair<std::string, std::string>>& parameters,
                           int max_attempts = 1);
    
    bool cancel(work::ExecutionId exec_id);
    
    ExecutionResult get_execution(work::ExecutionId exec_id) const;
    
    ExecutionMetrics metrics() const;

private:
    core::Outcome execute_attempt(const work::Task& task, int attempt_number);
    
    void record_execution_state(work::ExecutionId exec_id, UnitExecutionState state);
    
    // Subprocess executor for native execution
    std::unique_ptr<rebuntu::runtime::SubprocessExecutor> subprocess_executor_;
    
    // Execution records storage (simplified - in production would use database/IPC)
    mutable std::mutex executions_mutex_;
    std::unordered_map<work::ExecutionId, ExecutionResult> executions_;
    
    // Metrics (thread-safe via mutex)
    mutable std::mutex metrics_mutex_;
    ExecutionMetrics metrics_;
    
    // Next execution ID counter
    mutable std::mutex id_mutex_;
    int next_execution_counter_ = 0;
};

std::unique_ptr<UnitExecutor> make_unit_executor();

}  // namespace rebuntu::runtime::unit_executor