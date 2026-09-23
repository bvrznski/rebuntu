#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::monotonic::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/time/monotonic/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::monotonic::contracts::inputs
