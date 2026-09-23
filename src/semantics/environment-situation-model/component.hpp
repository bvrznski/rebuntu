#pragma once

#include <string_view>

namespace rebuntu::semantics::environment_situation_model {

// Structural integration point for environment situation model.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class EnvironmentSituationModelComponent {
public:
    virtual ~EnvironmentSituationModelComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "environment-situation-model"; }
};

} // namespace rebuntu::semantics::environment_situation_model
