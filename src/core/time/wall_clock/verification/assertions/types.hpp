#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::wall_clock::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/time/wall_clock/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::wall_clock::verification::assertions
