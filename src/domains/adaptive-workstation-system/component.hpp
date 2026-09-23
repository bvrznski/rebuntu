#pragma once

#include <string_view>

namespace rebuntu::domains::adaptive_workstation_system {

// Structural integration point for adaptive workstation system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class AdaptiveWorkstationSystemComponent {
public:
    virtual ~AdaptiveWorkstationSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "adaptive-workstation-system"; }
};

} // namespace rebuntu::domains::adaptive_workstation_system
