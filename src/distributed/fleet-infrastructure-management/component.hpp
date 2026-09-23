#pragma once

#include <string_view>

namespace rebuntu::distributed::fleet_infrastructure_management {

// Structural integration point for fleet infrastructure management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class FleetInfrastructureManagementComponent {
public:
    virtual ~FleetInfrastructureManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "fleet-infrastructure-management"; }
};

} // namespace rebuntu::distributed::fleet_infrastructure_management
