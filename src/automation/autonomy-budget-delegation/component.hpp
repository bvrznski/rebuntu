#pragma once

#include <string_view>

namespace rebuntu::automation::autonomy_budget_delegation {

// Structural integration point for autonomy budget delegation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class AutonomyBudgetDelegationComponent {
public:
    virtual ~AutonomyBudgetDelegationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "autonomy-budget-delegation"; }
};

} // namespace rebuntu::automation::autonomy_budget_delegation
