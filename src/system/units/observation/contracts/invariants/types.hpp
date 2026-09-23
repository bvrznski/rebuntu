#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::observation::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/units/observation/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::observation::contracts::invariants
