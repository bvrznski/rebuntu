#pragma once

#include <string_view>

namespace rebuntu::control::stability_and_recovery {

// Structural integration point for stability and recovery.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class StabilityAndRecoveryComponent {
public:
    virtual ~StabilityAndRecoveryComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "stability-and-recovery"; }
};

} // namespace rebuntu::control::stability_and_recovery
