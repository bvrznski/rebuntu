#pragma once

#include <string_view>

namespace rebuntu::runtime::environment_coordination {

// Structural integration point for environment coordination.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class EnvironmentCoordinationComponent {
public:
    virtual ~EnvironmentCoordinationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "environment-coordination"; }
};

} // namespace rebuntu::runtime::environment_coordination
