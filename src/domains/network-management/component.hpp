#pragma once

#include <string_view>

namespace rebuntu::domains::network_management {

// Structural integration point for network management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class NetworkManagementComponent {
public:
    virtual ~NetworkManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "network-management"; }
};

} // namespace rebuntu::domains::network_management
