#pragma once

#include <string_view>

namespace rebuntu::control::transactional_change_safe_transition {

// Structural integration point for transactional change safe transition.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class TransactionalChangeSafeTransitionComponent {
public:
    virtual ~TransactionalChangeSafeTransitionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "transactional-change-safe-transition"; }
};

} // namespace rebuntu::control::transactional_change_safe_transition
