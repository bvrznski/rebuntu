#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::consistency {
struct ConsistencySkeleton final {
    static constexpr std::string_view path = "src/system/state/consistency";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::consistency
