#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::signal {
struct SignalSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/signal";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::signal
