#pragma once

#include <string_view>

namespace rebuntu::operator_ui::explainable_autonomous_operations {

// Structural integration point for explainable autonomous operations.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ExplainableAutonomousOperationsComponent {
public:
    virtual ~ExplainableAutonomousOperationsComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "explainable-autonomous-operations"; }
};

} // namespace rebuntu::operator_ui::explainable_autonomous_operations
