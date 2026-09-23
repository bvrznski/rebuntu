#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::dependency::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/units/dependency/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::dependency::contracts::invariants
