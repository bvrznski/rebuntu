#pragma once

#include <string_view>

namespace rebuntu::domains::development_environment_management {

// Structural integration point for development environment management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class DevelopmentEnvironmentManagementComponent {
public:
    virtual ~DevelopmentEnvironmentManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "development-environment-management"; }
};

} // namespace rebuntu::domains::development_environment_management
