#pragma once

#include <string_view>

namespace rebuntu::runtime::maintenance {

// Structural integration point for maintenance.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class MaintenanceComponent {
public:
    virtual ~MaintenanceComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "maintenance"; }
};

} // namespace rebuntu::runtime::maintenance
