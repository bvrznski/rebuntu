#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::conflict::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/conflict/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::conflict::contracts::invariants
