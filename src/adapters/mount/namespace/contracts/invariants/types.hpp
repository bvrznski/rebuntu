#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::mount::namespace_node::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/mount/namespace/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::mount::namespace_node::contracts::invariants
