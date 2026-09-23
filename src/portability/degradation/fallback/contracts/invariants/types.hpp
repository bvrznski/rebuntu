#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::fallback::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/fallback/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::fallback::contracts::invariants
