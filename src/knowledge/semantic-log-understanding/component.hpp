#pragma once

#include <string_view>

namespace rebuntu::knowledge::semantic_log_understanding {

// Structural integration point for semantic log understanding.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SemanticLogUnderstandingComponent {
public:
    virtual ~SemanticLogUnderstandingComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "semantic-log-understanding"; }
};

} // namespace rebuntu::knowledge::semantic_log_understanding
