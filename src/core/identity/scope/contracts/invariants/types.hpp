#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::scope::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/identity/scope/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::scope::contracts::invariants
