#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::deprecation::retirement {
struct RetirementSkeleton final {
    static constexpr std::string_view path = "src/governance/deprecation/retirement";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::deprecation::retirement
