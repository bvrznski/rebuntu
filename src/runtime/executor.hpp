// rebuntu::runtime::executor — Executor implementation (Phase 0.13)
#pragma once

#include <runtime/contracts.hpp>
#include <runtime/work.hpp>
#include <runtime/core/contracts.hpp>
#include <chrono>
#include <functional>
#include <optional>
#include <string>

namespace rebuntu::runtime::executor {

enum class ExecutionModeSelector {
    kInline,
    kSubprocess,
    kSystemdUnit,
    kDBusMethod,
};

inline std::string_view to_string(ExecutionModeSelector m) {
    switch (m) {
        case ExecutionModeSelector::kInline: return "inline";
        case ExecutionModeSelector::kSubprocess: return "subprocess";
        case ExecutionModeSelector::kSystemdUnit: return "systemd-unit";
        case ExecutionModeSelector::kDBusMethod: return "dbus-method";
    }
    return "unknown";
}

struct ExecutorInvocationContext {
    runtime::TimeoutPolicy timeout_policy;
    std::optional<std::chrono::system_clock::time_point> deadline;
    bool cancellation_requested = false;
};

struct ExecutorResult {
    core::Outcome outcome;
    work::ExecutionId execution_id;
    work::AttemptNumber attempt_number;
    bool is_last_attempt = true;
    std::chrono::milliseconds preparation_duration{0};
    std::chrono::milliseconds execution_duration{0};
    std::chrono::milliseconds verification_duration{0};
};

class Executor {
public:
    using ExecuteFn = std::function<core::Outcome(const work::Task&, 
                                                   const ExecutorInvocationContext&)>;
    
    explicit Executor(ExecuteFn execute_fn) : execute_fn_(std::move(execute_fn)) {}
    
    virtual ~Executor() = default;
    
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

class InlineExecutor : public Executor {
public:
    InlineExecutor();
    
    core::Outcome execute_inline(const work::Task&, std::function<core::Outcome()> op);
};

}  // namespace rebuntu::runtime::executor
