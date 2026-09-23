#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::monotonic {
struct MonotonicSkeleton final {
    static constexpr std::string_view path = "src/core/time/monotonic";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::monotonic
