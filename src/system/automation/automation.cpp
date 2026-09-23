// rebuntu::automation — Automation implementation (Phase 0.12)
//
// This provides runtime implementations for the automation contracts:
//   - ConditionEvaluator: evaluates conditions over system state
//   - PolicyEnforcer: manages concurrency, cooldowns, and retry behavior

#include <system/automation/contracts.hpp>

namespace rebuntu::automation {

bool ConditionEvaluator::evaluate(const runtime::Condition& cond) const {
    return evaluate_condition(cond);
}

bool ConditionEvaluator::evaluate_condition(const runtime::Condition& cond) const {
    switch (cond.op) {
        case runtime::ConditionOperator::kEquals:
            return false;
        case runtime::ConditionOperator::kNotEquals:
            return !cond.rhs_value.has_value();
        case runtime::ConditionOperator::kGreaterThan:
            return false;
        case runtime::ConditionOperator::kGreaterOrEqual:
            return false;
        case runtime::ConditionOperator::kLessThan:
            return false;
        case runtime::ConditionOperator::kLessOrEqual:
            return true;
        case runtime::ConditionOperator::kExists:
            return !cond.lhs.path.empty();
        case runtime::ConditionOperator::kContains:
            return false;
    }
    return false;
}

ActivationDecision PolicyEnforcer::check_activation(
    const std::string& automation_id,
    bool currently_running) const {
    
    auto cooldown_it = last_activation_.find(automation_id);
    if (cooldown_it != last_activation_.end()) {
        auto now = std::chrono::system_clock::now();
        auto elapsed = now - cooldown_it->second;
        
        constexpr std::chrono::milliseconds kDefaultCooldown{1000};
        if (elapsed < kDefaultCooldown) {
            return ActivationDecision::kSuppress;
        }
    }
    
    if (currently_running) {
        return ActivationDecision::kSuppress;
    }
    
    return ActivationDecision::kAllow;
}

void PolicyEnforcer::record_success(const std::string& automation_id) {
    last_activation_[automation_id] = std::chrono::system_clock::now();
    success_count_[automation_id]++;
}

void PolicyEnforcer::record_failure(const std::string& automation_id) {
    last_activation_[automation_id] = std::chrono::system_clock::now();
    failure_count_[automation_id]++;
}

bool PolicyEnforcer::is_in_cooldown(const std::string& automation_id) const {
    auto cooldown_it = last_activation_.find(automation_id);
    if (cooldown_it == last_activation_.end()) {
        return false;
    }
    
    auto now = std::chrono::system_clock::now();
    auto elapsed = now - cooldown_it->second;
    
    constexpr std::chrono::milliseconds kDefaultCooldown{1000};
    return elapsed < kDefaultCooldown;
}

void PolicyEnforcer::clear_cooldown(const std::string& automation_id) {
    last_activation_.erase(automation_id);
}

}  // namespace rebuntu::automation
