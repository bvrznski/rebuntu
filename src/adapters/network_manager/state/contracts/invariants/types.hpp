#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::state::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/state/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::state::contracts::invariants
