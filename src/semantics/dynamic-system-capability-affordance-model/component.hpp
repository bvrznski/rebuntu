#pragma once

#include <string_view>

namespace rebuntu::semantics::dynamic_system_capability_affordance_model {

// Structural integration point for dynamic system capability affordance model.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class DynamicSystemCapabilityAffordanceModelComponent {
public:
    virtual ~DynamicSystemCapabilityAffordanceModelComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "dynamic-system-capability-affordance-model"; }
};

} // namespace rebuntu::semantics::dynamic_system_capability_affordance_model
