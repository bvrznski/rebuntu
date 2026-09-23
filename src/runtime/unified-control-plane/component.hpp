#pragma once

#include <string_view>

namespace rebuntu::runtime::unified_control_plane {

// Structural integration point for unified control plane.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class UnifiedControlPlaneComponent {
public:
    virtual ~UnifiedControlPlaneComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "unified-control-plane"; }
};

} // namespace rebuntu::runtime::unified_control_plane
