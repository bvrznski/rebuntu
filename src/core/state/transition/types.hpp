#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::transition {
struct TransitionSkeleton final {
    static constexpr std::string_view path = "src/core/state/transition";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::transition
