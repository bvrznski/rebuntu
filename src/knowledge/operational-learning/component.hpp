#pragma once

#include <string_view>

namespace rebuntu::knowledge::operational_learning {

// Structural integration point for operational learning.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OperationalLearningComponent {
public:
    virtual ~OperationalLearningComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "operational-learning"; }
};

} // namespace rebuntu::knowledge::operational_learning
