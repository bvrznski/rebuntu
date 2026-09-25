// rebuntu::runtime::dispatcher — Execution Dispatcher (Phase 0.13)
//
// The Dispatcher routes eligible work to appropriate execution mechanisms/providers.
//
// Key semantics established here:
//   * Dispatcher does NOT execute work (that's Executor)
//   * Dispatcher makes routing decisions based on policy
//   * Dispatcher tracks pending work for backpressure

#pragma once

#include <runtime/work.hpp>
#include <runtime/core/contracts.hpp>
#include <string>
#include <functional>
#include <optional>
#include <map>

namespace rebuntu::runtime::dispatcher {

struct ExecutionModeSelection {
    runtime::work::ExecutionMode mode;
    std::string reason;
};

struct DispatcherContext {
    bool subprocess_available = true;
    bool systemd_unit_available = false;
    bool dbus_available = false;
    size_t pending_work_count = 0;
    size_t max_concurrent_executions = 100;
    std::optional<std::string> scope;
};

struct DispatcherDecision {
    bool accepted;
    ExecutionModeSelection selection;
    std::optional<core::Error> error;
    
    static DispatcherDecision accept(ExecutionModeSelection sel) {
        return {true, std::move(sel), std::nullopt};
    }
    
    static DispatcherDecision reject(std::string code, std::string message) {
        return {false,
                ExecutionModeSelection{runtime::work::ExecutionMode::kInline, "rejected"},
                core::Error{std::move(code), std::move(message)}};
    }
};

// Dispatcher makes routing decisions for work
//
// The Dispatcher does NOT execute tasks. It:
//   - Evaluates Task requirements against available mechanisms
//   - Selects appropriate execution mode (inline, subprocess, systemd, etc.)
//   - Tracks pending work count for backpressure
//   - Enforces concurrency limits
//
class Dispatcher {
public:
    using DispatchCallback = std::function<void(const runtime::work::Job&)>;
    
    explicit Dispatcher(DispatchCallback on_dispatch)
        : on_dispatch_(std::move(on_dispatch)) {}
    
    // Select execution mode based on task requirements and available mechanisms
    ExecutionModeSelection select_execution_mode(
        const runtime::work::Task& task,
        const DispatcherContext& ctx) const;
    
    // Dispatch a job - invokes callback if accepted
    DispatcherDecision dispatch(
        const runtime::work::Job& job,
        const DispatcherContext& ctx);
    
    bool is_backpressured() const {
        return pending_work_count_ >= max_concurrent_executions_;
    }
    
    void increment_pending();
    void decrement_pending();
    
    size_t get_pending_count() const { return pending_work_count_; }

private:
    DispatchCallback on_dispatch_;
    size_t pending_work_count_ = 0;
    size_t max_concurrent_executions_ = 100;
};

// DispatcherRegistry maintains known execution mechanisms
//
// This is a DATA structure - it does NOT manage lifecycle or execution.
//
class DispatcherRegistry {
public:
    void register_mechanism(std::string name, runtime::work::ExecutionMode mode) {
        mechanisms_[std::move(name)] = mode;
    }
    
    std::optional<runtime::work::ExecutionMode> find_mechanism(
        const std::string& capability_id) const {
        auto it = mechanisms_.find(capability_id);
        if (it != mechanisms_.end()) {
            return it->second;
        }
        
        // Fallback: partial name match
        for (const auto& [name, mode] : mechanisms_) {
            if (capability_id.find(name) != std::string::npos) {
                return mode;
            }
        }
        
        return std::nullopt;
    }
    
    std::vector<std::pair<std::string, runtime::work::ExecutionMode>> all() const {
        std::vector<std::pair<std::string, runtime::work::ExecutionMode>> result;
        for (const auto& [name, mode] : mechanisms_) {
            result.emplace_back(name, mode);
        }
        return result;
    }

private:
    std::map<std::string, runtime::work::ExecutionMode> mechanisms_;
};

// Factory function
inline std::unique_ptr<Dispatcher> make_dispatcher(
    Dispatcher::DispatchCallback on_dispatch) {
    return std::make_unique<Dispatcher>(std::move(on_dispatch));
}

}  // namespace rebuntu::runtime::dispatcher

// Implementation section
inline void rebuntu::runtime::dispatcher::Dispatcher::increment_pending() {
    if (pending_work_count_ < max_concurrent_executions_) {
        pending_work_count_++;
    }
}

inline void rebuntu::runtime::dispatcher::Dispatcher::decrement_pending() {
    if (pending_work_count_ > 0) {
        pending_work_count_--;
    }
}

inline rebuntu::runtime::dispatcher::ExecutionModeSelection 
rebuntu::runtime::dispatcher::Dispatcher::select_execution_mode(
    const runtime::work::Task& task,
    const DispatcherContext& ctx) const {
    
    // For now, use the mode specified in the task
    if (task.mode != runtime::work::ExecutionMode::kInline && !ctx.subprocess_available) {
        return ExecutionModeSelection{
            runtime::work::ExecutionMode::kInline,
            "subprocess not available, falling back to inline"
        };
    }
    
    return ExecutionModeSelection{task.mode, "task-specified mode"};
}

inline rebuntu::runtime::dispatcher::DispatcherDecision 
rebuntu::runtime::dispatcher::Dispatcher::dispatch(
    const runtime::work::Job& job,
    const DispatcherContext& ctx) {
    
    // Check backpressure
    if (is_backpressured()) {
        return DispatcherDecision::reject(
            "E_BACKPRESSURE",
            "too many pending executions");
    }
    
    auto selection = select_execution_mode(job, ctx);
    
    if (selection.mode == runtime::work::ExecutionMode::kInline) {
        // Inline execution - immediate dispatch
        on_dispatch_(job);
        return DispatcherDecision::accept(selection);
    } else {
        // Non-inline execution - increment pending and dispatch
        increment_pending();
        on_dispatch_(job);
        return DispatcherDecision::accept(selection);
    }
}

namespace rebuntu { namespace runtime { namespace dispatcher {
struct Error {};
}}}  // namespace