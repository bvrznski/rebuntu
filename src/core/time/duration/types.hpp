#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::duration {
struct DurationSkeleton final {
    static constexpr std::string_view path = "src/core/time/duration";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::duration
