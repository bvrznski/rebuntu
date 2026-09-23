#pragma once

#include <string_view>

namespace rebuntu::semantics::os_task_context_awareness_system {

// Structural integration point for os task context awareness system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OsTaskContextAwarenessSystemComponent {
public:
    virtual ~OsTaskContextAwarenessSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "os-task-context-awareness-system"; }
};

} // namespace rebuntu::semantics::os_task_context_awareness_system
