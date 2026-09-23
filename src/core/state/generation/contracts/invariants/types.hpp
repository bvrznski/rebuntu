#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::generation::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/state/generation/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::generation::contracts::invariants
