#pragma once

#include <string_view>

namespace rebuntu::planning::long_horizon_operational_planning {

// Structural integration point for long horizon operational planning.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class LongHorizonOperationalPlanningComponent {
public:
    virtual ~LongHorizonOperationalPlanningComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "long-horizon-operational-planning"; }
};

} // namespace rebuntu::planning::long_horizon_operational_planning
