#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::method_call::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/method_call/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::method_call::contracts::invariants
