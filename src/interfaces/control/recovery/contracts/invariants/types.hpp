#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::recovery::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/recovery/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::recovery::contracts::invariants
