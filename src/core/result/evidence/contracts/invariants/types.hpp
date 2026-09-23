#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::evidence::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/result/evidence/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::evidence::contracts::invariants
