#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::goal {
struct GoalSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/goal";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::goal
