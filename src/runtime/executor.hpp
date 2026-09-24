// rebuntu::runtime::executor — Executor (Phase 0.13)
//
// The Executor invokes concrete implementations/providers and returns structured
// runtime observations/results.
//
// Key semantics established here:
//   * Executor is NOT a state machine (that's Runner)
//   * Executor executes one attempt, returns Outcome
//   * Executor knows about execution mechanisms but not retry logic

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/contracts.hpp>
#include <chrono>
#include <functional>
#include <optional>

namespace rebuntu::runtime::executor {

// ExecutionModeSelector identifies how to execute a task
enum class ExecutionModeSelector {
    kInline,        // In-process function call
    kSubprocess,    // OS subprocess (fork/execve)
    kSystemdUnit,   // systemd transient/managed unit
    kDBusMethod,    // D-Bus method invocation
    kThread         // Thread-based parallel execution
};

inline std::string to_string(ExecutionModeSelector m) {
    switch (m) {
        case ExecutionModeSelector::kInline: return "inline";
        case ExecutionModeSelector::kSubprocess: return "subprocess";
        case ExecutionModeSelector::kSystemdUnit: return "systemd-unit";
        case ExecutionModeSelector::kDBusMethod: return "dbus-method";
        case ExecutionModeSelector::kThread: return "thread";
    }
    return "unknown";
}

// ExecutorInvocationContext holds parameters for one execution attempt
struct ExecutorInvocationContext {
    runtime::TimeoutPolicy timeout_policy;
    std::optional<std::chrono::system_clock::time_point> deadline;
    bool cancellation_requested = false;
};

// ExecutorResult captures the outcome of one execution attempt
struct ExecutorResult {
    core::Outcome outcome;
    work::ExecutionId execution_id;
    work::AttemptNumber attempt_number;
    bool is_last_attempt = true;
    std::chrono::milliseconds preparation_duration{0};
    std::chrono::milliseconds execution_duration{0};
    std::chrono::milliseconds verification_duration{0};
};

// Executor is the abstract interface for execution mechanisms
//
// An Executor executes ONE attempt of a task. It:
//   - Takes Task, Job, and context as input
//   - Executes using a specific mechanism (inline, subprocess, etc.)
//   - Returns Outcome with evidence
//
class Executor {
public:
    using ExecuteFn = std::function<core::Outcome(const work::Task&, 
                                                   const work::Job&,
                                                   const ExecutorInvocationContext&)>;
    
    explicit Executor(ExecuteFn execute_fn) : execute_fn_(std::move(execute_fn)) {}
    
    virtual ~Executor() = default;
    
    // Execute one attempt of a job
    virtual ExecutorResult execute(
        const work::Task& task,
        const work::Job& job,
        const ExecutorInvocationContext& ctx);
    
    int total_invocations() const { return total_invocations_; }
    int successful_executions() const { return successful_executions_; }
    int failed_executions() const { return failed_executions_; }

protected:
    ExecuteFn execute_fn_;
    int total_invocations_ = 0;
    int successful_executions_ = 0;
    int failed_executions_ = 0;
};

// InlineExecutor executes in-process without spawning subprocesses
//
// Used for:
//   - Testing
//   - Lightweight read-only operations
//   - Pure function execution
//
class InlineExecutor : public Executor {
public:
    InlineExecutor();
    
    // Execute an inline operation, returning Outcome
    core::Outcome execute_inline(const work::Task&, std::function<core::Outcome()> op);
};

}  // namespace rebuntu::runtime::executor

// Implementation section
inline rebuntu::runtime::executor::ExecutorResult 
rebuntu::runtime::executor::Executor::execute(
    const work::Task& task,
    const work::Job& job,
    const ExecutorInvocationContext& ctx) {
    
    total_invocations_++;
    
    auto start_time = std::chrono::system_clock::now();
    
    core::Outcome outcome = execute_fn_(task, job, ctx);
    
    auto end_time = std::chrono::system_clock::now();
    auto exec_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    if (outcome.status == core::SemanticStatus::kSuccess) {
        successful_executions_++;
    } else {
        failed_executions_++;
    }
    
    return ExecutorResult{
        outcome,
        work::ExecutionId{job.id.value},
        work::AttemptNumber{1},
        /*is_last_attempt=*/true,
        std::chrono::milliseconds(0),
        exec_duration,
        std::chrono::milliseconds(0)
    };
}

inline rebuntu::runtime::executor::InlineExecutor::InlineExecutor() 
    : Executor([](const work::Task&, const work::Job&,
                  const ExecutorInvocationContext&) { 
        return core::Outcome::unknown("not implemented"); 
    }) {
}

inline core::Outcome rebuntu::runtime::executor::InlineExecutor::execute_inline(
    const work::Task&, 
    std::function<core::Outcome()> op) {
    return op();
}

namespace rebuntu { namespace runtime { namespace executor {
struct Error {};
}}}  // namespace