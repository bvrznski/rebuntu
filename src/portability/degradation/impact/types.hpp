#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::impact {
struct ImpactSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/impact";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::impact
