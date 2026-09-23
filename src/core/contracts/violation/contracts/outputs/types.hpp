#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::violation::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/violation/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::violation::contracts::outputs
