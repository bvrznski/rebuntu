#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::duration::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/time/duration/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::duration::contracts::outputs
