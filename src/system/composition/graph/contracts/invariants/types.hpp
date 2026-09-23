#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::graph::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/composition/graph/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::graph::contracts::invariants
