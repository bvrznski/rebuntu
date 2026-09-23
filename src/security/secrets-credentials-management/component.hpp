#pragma once

#include <string_view>

namespace rebuntu::security::secrets_credentials_management {

// Structural integration point for secrets credentials management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SecretsCredentialsManagementComponent {
public:
    virtual ~SecretsCredentialsManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "secrets-credentials-management"; }
};

} // namespace rebuntu::security::secrets_credentials_management
