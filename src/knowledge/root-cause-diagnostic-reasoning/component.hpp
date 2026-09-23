#pragma once

#include <string_view>

namespace rebuntu::knowledge::root_cause_diagnostic_reasoning {

// Structural integration point for root cause diagnostic reasoning.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class RootCauseDiagnosticReasoningComponent {
public:
    virtual ~RootCauseDiagnosticReasoningComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "root-cause-diagnostic-reasoning"; }
};

} // namespace rebuntu::knowledge::root_cause_diagnostic_reasoning
