#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::lease::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/time/lease/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::lease::verification::assertions
