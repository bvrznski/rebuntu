#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::transitions {
struct TransitionsSkeleton final {
    static constexpr std::string_view path = "src/system/state/transitions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::transitions
