#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::timeouts {
struct TimeoutsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/timeouts";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::timeouts
