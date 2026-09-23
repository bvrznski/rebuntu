#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::observed {
struct ObservedSkeleton final {
    static constexpr std::string_view path = "src/core/state/observed";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::observed
