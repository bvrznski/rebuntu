#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::assessment {
struct AssessmentSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/assessment";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::assessment
