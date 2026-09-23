#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::action::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/action/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::action::contracts::invariants
