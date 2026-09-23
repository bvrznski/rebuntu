#pragma once

#include <string_view>

namespace rebuntu::domains::configuration_management {

// Structural integration point for configuration management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ConfigurationManagementComponent {
public:
    virtual ~ConfigurationManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "configuration-management"; }
};

} // namespace rebuntu::domains::configuration_management
