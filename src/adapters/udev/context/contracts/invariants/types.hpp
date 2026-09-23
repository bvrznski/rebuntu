#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::context::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/context/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::context::contracts::invariants
