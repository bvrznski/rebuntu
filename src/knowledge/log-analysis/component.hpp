#pragma once

#include <string_view>

namespace rebuntu::knowledge::log_analysis {

// Structural integration point for log analysis.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class LogAnalysisComponent {
public:
    virtual ~LogAnalysisComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "log-analysis"; }
};

} // namespace rebuntu::knowledge::log_analysis
