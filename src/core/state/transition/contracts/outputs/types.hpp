#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::transition::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/state/transition/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::transition::contracts::outputs
