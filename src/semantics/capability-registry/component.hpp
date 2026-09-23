#pragma once

#include <string_view>

namespace rebuntu::semantics::capability_registry {

// Structural integration point for capability registry.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class CapabilityRegistryComponent {
public:
    virtual ~CapabilityRegistryComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "capability-registry"; }
};

} // namespace rebuntu::semantics::capability_registry
