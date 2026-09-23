#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::predicate {
struct PredicateSkeleton final {
    static constexpr std::string_view path = "src/core/verification/predicate";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::predicate
