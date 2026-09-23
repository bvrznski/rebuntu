#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::assessment {
struct AssessmentSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/assessment";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::assessment
