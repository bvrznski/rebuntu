#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::monotonic::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/time/monotonic/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::monotonic::contracts::outputs
