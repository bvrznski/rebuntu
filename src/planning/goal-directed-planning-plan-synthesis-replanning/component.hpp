#pragma once

#include <string_view>

namespace rebuntu::planning::goal_directed_planning_plan_synthesis_replanning {

// Structural integration point for goal directed planning plan synthesis replanning.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class GoalDirectedPlanningPlanSynthesisReplanningComponent {
public:
    virtual ~GoalDirectedPlanningPlanSynthesisReplanningComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "goal-directed-planning-plan-synthesis-replanning"; }
};

} // namespace rebuntu::planning::goal_directed_planning_plan_synthesis_replanning
