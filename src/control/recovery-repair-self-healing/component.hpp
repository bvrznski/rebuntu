#pragma once

#include <string_view>

namespace rebuntu::control::recovery_repair_self_healing {

// Structural integration point for recovery repair self healing.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class RecoveryRepairSelfHealingComponent {
public:
    virtual ~RecoveryRepairSelfHealingComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "recovery-repair-self-healing"; }
};

} // namespace rebuntu::control::recovery_repair_self_healing
