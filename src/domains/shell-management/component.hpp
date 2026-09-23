#pragma once

#include <string_view>

namespace rebuntu::domains::shell_management {

// Structural integration point for shell management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ShellManagementComponent {
public:
    virtual ~ShellManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "shell-management"; }
};

} // namespace rebuntu::domains::shell_management
