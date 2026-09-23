#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::audit::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/audit/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::audit::contracts::invariants
