#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::audit::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/audit/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::audit::contracts::invariants
