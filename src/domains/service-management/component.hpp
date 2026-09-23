#pragma once

#include <string_view>

namespace rebuntu::domains::service_management {

// Structural integration point for service management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ServiceManagementComponent {
public:
    virtual ~ServiceManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "service-management"; }
};

} // namespace rebuntu::domains::service_management
