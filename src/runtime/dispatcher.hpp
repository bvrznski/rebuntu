// rebuntu::runtime::dispatcher — Execution Dispatcher (Phase 0.13)

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

class Dispatcher {
public:
    using DispatchCallback = std::function<void(const runtime::work::Job&)>;

    explicit Dispatcher(DispatchCallback on_dispatch)
        : on_dispatch_(std::move(on_dispatch)) {}

    ExecutionModeSelection select_execution_mode(
        const runtime::work::Task& task,
        const DispatcherContext& ctx) const;

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

}  // namespace rebuntu::runtime::dispatcher
