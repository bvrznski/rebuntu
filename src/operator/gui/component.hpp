#pragma once

#include <string_view>

namespace rebuntu::operator_ui::gui {

// Structural integration point for gui.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class GuiComponent {
public:
    virtual ~GuiComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "gui"; }
};

} // namespace rebuntu::operator_ui::gui
