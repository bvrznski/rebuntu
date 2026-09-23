#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::feature_negotiation::requirement {
struct RequirementSkeleton final {
    static constexpr std::string_view path = "src/portability/feature_negotiation/requirement";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::feature_negotiation::requirement
