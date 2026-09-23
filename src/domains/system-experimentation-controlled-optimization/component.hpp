#pragma once

#include <string_view>

namespace rebuntu::domains::system_experimentation_controlled_optimization {

// Structural integration point for system experimentation controlled optimization.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemExperimentationControlledOptimizationComponent {
public:
    virtual ~SystemExperimentationControlledOptimizationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-experimentation-controlled-optimization"; }
};

} // namespace rebuntu::domains::system_experimentation_controlled_optimization
