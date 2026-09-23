#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::step::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/step/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::step::contracts::invariants
