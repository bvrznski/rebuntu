#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::effective {
struct EffectiveSkeleton final {
    static constexpr std::string_view path = "src/core/state/effective";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::effective
