#pragma once

#include <string_view>

namespace rebuntu::security::policy_authorization_safety {

// Structural integration point for policy authorization safety.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class PolicyAuthorizationSafetyComponent {
public:
    virtual ~PolicyAuthorizationSafetyComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "policy-authorization-safety"; }
};

} // namespace rebuntu::security::policy_authorization_safety
