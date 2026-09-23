#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::deprecation::window::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/deprecation/window/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::deprecation::window::contracts::invariants
