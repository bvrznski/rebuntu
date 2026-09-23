#pragma once

#include <string_view>

namespace rebuntu::runtime::os_task_policy_system {

// Structural integration point for os task policy system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OsTaskPolicySystemComponent {
public:
    virtual ~OsTaskPolicySystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "os-task-policy-system"; }
};

} // namespace rebuntu::runtime::os_task_policy_system
