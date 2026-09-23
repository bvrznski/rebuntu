#pragma once
#include "../../core/types.hpp"
#include <functional>
#include <sstream>
#include <string>

namespace rebuntu::security::policy {
enum class Decision { allow, deny, unknown };
struct AuthorizationContext {
    std::string principal;
    std::string policy_version;
    std::string plan_fingerprint;
    std::size_t attempt{0};
    bool compensation{false};
};
struct AuthorizationResult {
    Decision decision{Decision::unknown};
    std::string reason;
    std::string bound_fingerprint;
    bool allowed_for(std::string_view fingerprint) const noexcept {
        return decision == Decision::allow && !bound_fingerprint.empty() && bound_fingerprint == fingerprint;
    }
};
using AuthorizeMutation = std::function<AuthorizationResult(const core::NativeOperation&, const AuthorizationContext&)>;

inline std::string operation_fingerprint(const core::NativeOperation& op) {
    std::ostringstream out;
    out << op.provider << '\x1f' << op.verb << '\x1f' << op.target << '\x1f' << (op.mutating ? '1' : '0');
    for (const auto& [key, value] : op.arguments) out << '\x1e' << key << '=' << value;
    return out.str();
}

inline AuthorizationResult fail_closed_without_policy(const core::NativeOperation& op, const AuthorizationContext&) {
    if (!op.mutating) return {Decision::allow, "read-only operation", operation_fingerprint(op)};
    return {Decision::deny, "mutating operation has no authorization policy", {}};
}
} // namespace rebuntu::security::policy
