#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::audit {
struct AuditSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/audit";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::audit
