#pragma once

#include <string_view>

namespace rebuntu::planning::change_impact_consequence_analysis {

// Structural integration point for change impact consequence analysis.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ChangeImpactConsequenceAnalysisComponent {
public:
    virtual ~ChangeImpactConsequenceAnalysisComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "change-impact-consequence-analysis"; }
};

} // namespace rebuntu::planning::change_impact_consequence_analysis
