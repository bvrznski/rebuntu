#pragma once

#include <string_view>

namespace rebuntu::runtime::evergreen_platform {

// Structural integration point for evergreen platform.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class EvergreenPlatformComponent {
public:
    virtual ~EvergreenPlatformComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "evergreen-platform"; }
};

} // namespace rebuntu::runtime::evergreen_platform
