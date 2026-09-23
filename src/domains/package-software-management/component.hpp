#pragma once

#include <string_view>

namespace rebuntu::domains::package_software_management {

// Structural integration point for package software management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class PackageSoftwareManagementComponent {
public:
    virtual ~PackageSoftwareManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "package-software-management"; }
};

} // namespace rebuntu::domains::package_software_management
