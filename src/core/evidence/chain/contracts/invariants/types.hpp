#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::chain::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/chain/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::chain::contracts::invariants
