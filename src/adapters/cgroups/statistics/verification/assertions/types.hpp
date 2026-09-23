#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::statistics::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/statistics/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::statistics::verification::assertions
