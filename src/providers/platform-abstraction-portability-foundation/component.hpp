#pragma once

#include <string_view>

namespace rebuntu::providers::platform_abstraction_portability_foundation {

// Structural integration point for platform abstraction portability foundation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class PlatformAbstractionPortabilityFoundationComponent {
public:
    virtual ~PlatformAbstractionPortabilityFoundationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "platform-abstraction-portability-foundation"; }
};

} // namespace rebuntu::providers::platform_abstraction_portability_foundation
