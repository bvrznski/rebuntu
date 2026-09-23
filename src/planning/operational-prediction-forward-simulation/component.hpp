#pragma once

#include <string_view>

namespace rebuntu::planning::operational_prediction_forward_simulation {

// Structural integration point for operational prediction forward simulation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OperationalPredictionForwardSimulationComponent {
public:
    virtual ~OperationalPredictionForwardSimulationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "operational-prediction-forward-simulation"; }
};

} // namespace rebuntu::planning::operational_prediction_forward_simulation
