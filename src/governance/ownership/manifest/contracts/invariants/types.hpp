#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::manifest::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/manifest/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::manifest::contracts::invariants
