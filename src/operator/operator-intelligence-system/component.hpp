#pragma once

#include <string_view>

namespace rebuntu::operator_ui::operator_intelligence_system {

// Structural integration point for operator intelligence system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OperatorIntelligenceSystemComponent {
public:
    virtual ~OperatorIntelligenceSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "operator-intelligence-system"; }
};

} // namespace rebuntu::operator_ui::operator_intelligence_system
