#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::identity::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/identity/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::identity::contracts::invariants
