#pragma once

#include <string_view>

namespace rebuntu::security::security_policy_audit {

// Structural integration point for security policy audit.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SecurityPolicyAuditComponent {
public:
    virtual ~SecurityPolicyAuditComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "security-policy-audit"; }
};

} // namespace rebuntu::security::security_policy_audit
