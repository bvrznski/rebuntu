#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::constraint {
struct ConstraintSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/constraint";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::constraint
