#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::contract::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/contract/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::contract::contracts::invariants
