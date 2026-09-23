#pragma once

#include <string_view>

namespace rebuntu::automation::workflow_foundation {

// Structural integration point for workflow foundation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class WorkflowFoundationComponent {
public:
    virtual ~WorkflowFoundationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "workflow-foundation"; }
};

} // namespace rebuntu::automation::workflow_foundation
