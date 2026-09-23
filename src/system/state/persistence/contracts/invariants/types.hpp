#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::persistence::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/state/persistence/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::persistence::contracts::invariants
