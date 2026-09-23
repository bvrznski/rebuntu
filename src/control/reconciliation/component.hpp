#pragma once

#include <string_view>

namespace rebuntu::control::reconciliation {

// Structural integration point for reconciliation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ReconciliationComponent {
public:
    virtual ~ReconciliationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "reconciliation"; }
};

} // namespace rebuntu::control::reconciliation
