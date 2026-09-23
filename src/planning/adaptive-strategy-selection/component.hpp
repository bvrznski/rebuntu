#pragma once

#include <string_view>

namespace rebuntu::planning::adaptive_strategy_selection {

// Structural integration point for adaptive strategy selection.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class AdaptiveStrategySelectionComponent {
public:
    virtual ~AdaptiveStrategySelectionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "adaptive-strategy-selection"; }
};

} // namespace rebuntu::planning::adaptive_strategy_selection
