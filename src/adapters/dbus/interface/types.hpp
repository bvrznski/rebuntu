#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::interface {
struct InterfaceSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/interface";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::interface
