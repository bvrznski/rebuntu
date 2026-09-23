#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::feature_negotiation::degradation {
struct DegradationSkeleton final {
    static constexpr std::string_view path = "src/portability/feature_negotiation/degradation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::feature_negotiation::degradation
