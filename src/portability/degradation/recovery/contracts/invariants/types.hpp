#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::recovery::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/recovery/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::recovery::contracts::invariants
