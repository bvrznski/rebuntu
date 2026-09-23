#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::plan::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/plan/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::plan::verification::assertions
