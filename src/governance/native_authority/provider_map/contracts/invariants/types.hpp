#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::provider_map::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/provider_map/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::provider_map::contracts::invariants
