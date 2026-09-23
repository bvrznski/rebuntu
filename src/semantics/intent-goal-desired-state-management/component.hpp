#pragma once

#include <string_view>

namespace rebuntu::semantics::intent_goal_desired_state_management {

// Structural integration point for intent goal desired state management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class IntentGoalDesiredStateManagementComponent {
public:
    virtual ~IntentGoalDesiredStateManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "intent-goal-desired-state-management"; }
};

} // namespace rebuntu::semantics::intent_goal_desired_state_management
