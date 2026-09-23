#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::invariant::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/invariant/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::invariant::verification::assertions
