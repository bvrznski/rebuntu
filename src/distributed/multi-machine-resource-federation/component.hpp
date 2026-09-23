#pragma once

#include <string_view>

namespace rebuntu::distributed::multi_machine_resource_federation {

// Structural integration point for multi machine resource federation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class MultiMachineResourceFederationComponent {
public:
    virtual ~MultiMachineResourceFederationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "multi-machine-resource-federation"; }
};

} // namespace rebuntu::distributed::multi_machine_resource_federation
