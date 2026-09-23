#pragma once

#include <string_view>

namespace rebuntu::operator_ui::system_control_panel {

// Structural integration point for system control panel.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemControlPanelComponent {
public:
    virtual ~SystemControlPanelComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-control-panel"; }
};

} // namespace rebuntu::operator_ui::system_control_panel
