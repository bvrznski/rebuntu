// rebuntu::automation — Automation & Automaton architecture (Phase 0.12)
//
// This establishes Rebuntu's canonical model for automatic work activation:
//
//   AUTOMATION = WHEN + WHY to execute work
//   WORKFLOW   = HOW coordinated work proceeds  
//   OPERATION  = WHAT bounded system action is performed
//
// Automation is a DECLARED RELATIONSHIP between an ACTIVATION CONDITION
// and BOUNDED REBUNTU WORK, GOVERNED BY POLICY.
#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <map>

namespace rebuntu::automation {

enum class TriggerKind {
    kEvent,
    kSchedule,
    kConditionTrue,
    kRequest,
};

inline std::string_view to_string(TriggerKind k) {
    switch (k) {
        case TriggerKind::kEvent:       return "event";
        case TriggerKind::kSchedule:    return "schedule";
        case TriggerKind::kConditionTrue:return "condition_true";
        case TriggerKind::kRequest:     return "request";
    }
    return "unknown";
}

enum class ActivationDecision {
    kAllow,
    kSuppress,
    kCoalesce,
    kDefer,
    kReject,
};

inline std::string_view to_string(ActivationDecision d) {
    switch (d) {
        case ActivationDecision::kAllow:    return "allow";
        case ActivationDecision::kSuppress: return "suppress";
        case ActivationDecision::kCoalesce: return "coalesce";
        case ActivationDecision::kDefer:    return "defer";
        case ActivationDecision::kReject:   return "reject";
    }
    return "unknown";
}

struct ConcurrencyPolicy {
    bool allow_concurrent = false;
    bool suppress_while_running = true;
    std::optional<std::chrono::milliseconds> cooldown_after_activation;
};

struct ActivationPolicy {
    ConcurrencyPolicy concurrency;
    runtime::RetryPolicy retry_policy;
    runtime::TimeoutPolicy timeout_policy;
};

enum class TargetKind {
    kOperation,
    kWorkflow,
};

inline std::string_view to_string(TargetKind k) {
    switch (k) {
        case TargetKind::kOperation: return "operation";
        case TargetKind::kWorkflow:  return "workflow";
    }
    return "unknown";
}

struct TargetReference {
    TargetKind kind;
    std::string id;
};

struct AutomationDefinition {
    std::string id;
    std::optional<std::string> title;
    std::optional<std::string> description;
    runtime::Condition condition;
    TriggerKind trigger_kind = TriggerKind::kEvent;
    TargetReference target;
    ActivationPolicy policy;
    bool enabled = true;
    core::ComponentKind kind = core::ComponentKind::kUnit;
};

enum class AutomatonState {
    kIdle,
    kEvaluating,
    kActivating,
    kRunning,
    kWaiting,
};

inline std::string_view to_string(AutomatonState s) {
    switch (s) {
        case AutomatonState::kIdle:       return "idle";
        case AutomatonState::kEvaluating: return "evaluating";
        case AutomatonState::kActivating: return "activating";
        case AutomatonState::kRunning:    return "running";
        case AutomatonState::kWaiting:    return "waiting";
    }
    return "unknown";
}

struct ActivationRecord {
    std::string automation_id;
    TriggerKind trigger_kind;
    runtime::Condition triggered_condition;
    std::chrono::system_clock::time_point timestamp;
    ActivationDecision decision;
    TargetReference target;
};

struct AutomatonInstance {
    std::string definition_id;
    AutomatonState state = AutomatonState::kIdle;
    std::optional<ActivationRecord> current_activation;
    int total_activations_attempted = 0;
    int total_successes = 0;
    int total_failures = 0;
};

class AutomationRegistry {
public:
    void register_automation(AutomationDefinition def) {
        automations_[def.id] = std::move(def);
    }
    
    bool contains(std::string_view id) const {
        return automations_.find(std::string{id}) != automations_.end();
    }
    
    std::optional<AutomationDefinition> find(std::string_view id) const {
        auto it = automations_.find(std::string{id});
        if (it == automations_.end()) return std::nullopt;
        return it->second;
    }
    
    std::vector<AutomationDefinition> enabled() const {
        std::vector<AutomationDefinition> result;
        for (const auto& [id, aut] : automations_) {
            if (aut.enabled) {
                result.push_back(aut);
            }
        }
        return result;
    }
    
    std::vector<AutomationDefinition> all() const {
        std::vector<AutomationDefinition> result;
        for (const auto& [id, aut] : automations_) {
            result.push_back(aut);
        }
        return result;
    }

private:
    std::map<std::string, AutomationDefinition> automations_;
};

class ConditionEvaluator {
public:
    bool evaluate(const runtime::Condition& cond) const;

private:
    bool evaluate_condition(const runtime::Condition& cond) const;
};

class PolicyEnforcer {
public:
    ActivationDecision check_activation(
        const std::string& automation_id,
        bool currently_running) const;
    
    void record_success(const std::string& automation_id);
    
    void record_failure(const std::string& automation_id);
    
    bool is_in_cooldown(const std::string& automation_id) const;
    
    void clear_cooldown(const std::string& automation_id);

private:
    mutable std::map<std::string, std::chrono::system_clock::time_point> last_activation_;
    mutable std::map<std::string, int> success_count_;
    mutable std::map<std::string, int> failure_count_;
};

}  // namespace rebuntu::automation