#pragma once

#include <string_view>

namespace rebuntu::automation::automation_workflow_system {

// Structural integration point for automation workflow system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class AutomationWorkflowSystemComponent {
public:
    virtual ~AutomationWorkflowSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "automation-workflow-system"; }
};

} // namespace rebuntu::automation::automation_workflow_system
