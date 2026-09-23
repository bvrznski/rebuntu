#pragma once

#include <string_view>

namespace rebuntu::domains::user_identity_management {

// Structural integration point for user identity management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class UserIdentityManagementComponent {
public:
    virtual ~UserIdentityManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "user-identity-management"; }
};

} // namespace rebuntu::domains::user_identity_management
