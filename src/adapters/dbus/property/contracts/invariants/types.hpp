#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::property::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/property/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::property::contracts::invariants
