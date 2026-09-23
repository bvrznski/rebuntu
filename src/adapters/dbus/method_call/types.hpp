#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::method_call {
struct MethodCallSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/method_call";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::method_call
