#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::connection {
struct ConnectionSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/connection";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::connection
