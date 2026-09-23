#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::invariant {
struct InvariantSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/invariant";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::invariant
