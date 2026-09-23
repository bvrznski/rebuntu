#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::error::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/error/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::error::contracts::invariants
