#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::assessment {
struct AssessmentSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/assessment";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::assessment
