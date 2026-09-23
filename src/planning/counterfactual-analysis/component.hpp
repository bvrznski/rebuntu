#pragma once

#include <string_view>

namespace rebuntu::planning::counterfactual_analysis {

// Structural integration point for counterfactual analysis.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class CounterfactualAnalysisComponent {
public:
    virtual ~CounterfactualAnalysisComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "counterfactual-analysis"; }
};

} // namespace rebuntu::planning::counterfactual_analysis
