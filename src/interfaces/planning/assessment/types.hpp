#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::assessment {
struct AssessmentSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/assessment";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::assessment
