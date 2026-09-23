#pragma once

#include <string_view>

namespace rebuntu::domains::resource_management {

// Structural integration point for resource management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ResourceManagementComponent {
public:
    virtual ~ResourceManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "resource-management"; }
};

} // namespace rebuntu::domains::resource_management
