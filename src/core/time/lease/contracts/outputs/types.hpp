#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::lease::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/time/lease/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::lease::contracts::outputs
