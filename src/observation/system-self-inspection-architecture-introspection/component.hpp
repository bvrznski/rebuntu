#pragma once

#include <string_view>

namespace rebuntu::observation::system_self_inspection_architecture_introspection {

// Structural integration point for system self inspection architecture introspection.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemSelfInspectionArchitectureIntrospectionComponent {
public:
    virtual ~SystemSelfInspectionArchitectureIntrospectionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-self-inspection-architecture-introspection"; }
};

} // namespace rebuntu::observation::system_self_inspection_architecture_introspection
