#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::report::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/report/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::report::verification::assertions
