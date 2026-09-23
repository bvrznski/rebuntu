#pragma once

#include <string_view>

namespace rebuntu::domains::configuration_evolution_drift_governance {

// Structural integration point for configuration evolution drift governance.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ConfigurationEvolutionDriftGovernanceComponent {
public:
    virtual ~ConfigurationEvolutionDriftGovernanceComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "configuration-evolution-drift-governance"; }
};

} // namespace rebuntu::domains::configuration_evolution_drift_governance
