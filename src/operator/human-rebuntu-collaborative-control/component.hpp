#pragma once

#include <string_view>

namespace rebuntu::operator_ui::human_rebuntu_collaborative_control {

// Structural integration point for human rebuntu collaborative control.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class HumanRebuntuCollaborativeControlComponent {
public:
    virtual ~HumanRebuntuCollaborativeControlComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "human-rebuntu-collaborative-control"; }
};

} // namespace rebuntu::operator_ui::human_rebuntu_collaborative_control
