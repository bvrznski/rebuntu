#pragma once

#include <string_view>

namespace rebuntu::operator_ui::interrupt_escalation_attention_arbitration {

// Structural integration point for interrupt escalation attention arbitration.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class InterruptEscalationAttentionArbitrationComponent {
public:
    virtual ~InterruptEscalationAttentionArbitrationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "interrupt-escalation-attention-arbitration"; }
};

} // namespace rebuntu::operator_ui::interrupt_escalation_attention_arbitration
