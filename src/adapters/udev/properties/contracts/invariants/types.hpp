#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::properties::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/properties/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::properties::contracts::invariants
