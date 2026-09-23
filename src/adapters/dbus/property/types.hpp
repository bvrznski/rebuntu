#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::property {
struct PropertySkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/property";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::property
