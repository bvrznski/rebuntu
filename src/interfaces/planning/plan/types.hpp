#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::plan {
struct PlanSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/plan";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::plan
