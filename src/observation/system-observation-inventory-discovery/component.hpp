#pragma once

#include <string_view>

namespace rebuntu::observation::system_observation_inventory_discovery {

// Structural integration point for system observation inventory discovery.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemObservationInventoryDiscoveryComponent {
public:
    virtual ~SystemObservationInventoryDiscoveryComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-observation-inventory-discovery"; }
};

} // namespace rebuntu::observation::system_observation_inventory_discovery
