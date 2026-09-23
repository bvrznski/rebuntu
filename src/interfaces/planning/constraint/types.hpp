#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::constraint {
struct ConstraintSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/constraint";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::constraint
