#pragma once

#include <string_view>

namespace rebuntu::knowledge::experience_outcome_model {

// Structural integration point for experience outcome model.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ExperienceOutcomeModelComponent {
public:
    virtual ~ExperienceOutcomeModelComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "experience-outcome-model"; }
};

} // namespace rebuntu::knowledge::experience_outcome_model
