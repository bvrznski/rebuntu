#pragma once

#include <string_view>

namespace rebuntu::domains::terminal_management {

// Structural integration point for terminal management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class TerminalManagementComponent {
public:
    virtual ~TerminalManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "terminal-management"; }
};

} // namespace rebuntu::domains::terminal_management
