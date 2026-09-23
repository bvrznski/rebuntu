#pragma once

#include <string_view>

namespace rebuntu::runtime::resource_foundation {

// Structural integration point for resource foundation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ResourceFoundationComponent {
public:
    virtual ~ResourceFoundationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "resource-foundation"; }
};

} // namespace rebuntu::runtime::resource_foundation
