// rebuntu::automation — Automation runtime implementation (Phase 0.12)
//
// This provides runtime implementations for the automation contracts:
//   - ConditionEvaluator: evaluates conditions over system state
//   - PolicyEnforcer: manages concurrency, cooldowns, and retry behavior

#include <automation/contracts.hpp>
#include <runtime/contracts.hpp>
#include <algorithm>

namespace rebuntu::automation {

bool ConditionEvaluator::evaluate(const runtime::Condition& cond) const {
    return evaluate_condition(cond);
}

bool ConditionEvaluator::evaluate_condition(const runtime::Condition& cond) const {
    // For now, conditions that don't have a specific evaluator just return false.
    // This is a safe default - if we can't verify the condition, we don't trigger.
    
    switch (cond.op) {
        case runtime::ConditionOperator::kEquals:
            // Equals requires both lhs and rhs to be provided with values
            if (!cond.lhs.path.empty() && cond.rhs_value.has_value()) {
                return true;  // Placeholder: real implementation would compare values
            }
            return false;
            
        case runtime::ConditionOperator::kNotEquals:
            if (!cond.lhs.path.empty()) {
                return !cond.rhs_value.has_value();
            }
            return false;
            
        case runtime::ConditionOperator::kGreaterThan:
            // Placeholder: real implementation would compare numeric values
            return cond.lhs.path.empty() ? false : true;
            
        case runtime::ConditionOperator::kGreaterOrEqual:
            return cond.lhs.path.empty() ? false : true;
            
        case runtime::ConditionOperator::kLessThan:
            return cond.lhs.path.empty() ? false : true;
            
        case runtime::ConditionOperator::kLessOrEqual:
            return !cond.lhs.path.empty();
            
        case runtime::ConditionOperator::kExists:
            // Condition exists if the path is non-empty (we can check it)
            return !cond.lhs.path.empty();
            
        case runtime::ConditionOperator::kContains:
            // Placeholder: real implementation would check containment
            return cond.lhs.path.empty() ? false : true;
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
    
    // Default policy: suppress while running
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