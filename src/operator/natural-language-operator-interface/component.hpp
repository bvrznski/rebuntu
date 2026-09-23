#pragma once

#include <string_view>

namespace rebuntu::operator_ui::natural_language_operator_interface {

// Structural integration point for natural language operator interface.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class NaturalLanguageOperatorInterfaceComponent {
public:
    virtual ~NaturalLanguageOperatorInterfaceComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "natural-language-operator-interface"; }
};

} // namespace rebuntu::operator_ui::natural_language_operator_interface
