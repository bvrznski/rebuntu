#pragma once

#include <string_view>

namespace rebuntu::operator_ui::operational_attention_priority {

// Structural integration point for operational attention priority.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class OperationalAttentionPriorityComponent {
public:
    virtual ~OperationalAttentionPriorityComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "operational-attention-priority"; }
};

} // namespace rebuntu::operator_ui::operational_attention_priority
