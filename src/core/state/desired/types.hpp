#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::desired {
struct DesiredSkeleton final {
    static constexpr std::string_view path = "src/core/state/desired";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::desired
