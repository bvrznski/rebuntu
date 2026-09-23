#pragma once

#include <string_view>

namespace rebuntu::operator_ui::operator_preference_working_style {

// Structural integration point for operator preference working style.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OperatorPreferenceWorkingStyleComponent {
public:
    virtual ~OperatorPreferenceWorkingStyleComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "operator-preference-working-style"; }
};

} // namespace rebuntu::operator_ui::operator_preference_working_style
