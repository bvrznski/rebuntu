#pragma once

#include <string_view>

namespace rebuntu::observation::predictive_health {

// Structural integration point for predictive health.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class PredictiveHealthComponent {
public:
    virtual ~PredictiveHealthComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "predictive-health"; }
};

} // namespace rebuntu::observation::predictive_health
