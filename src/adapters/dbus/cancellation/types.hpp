#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::cancellation {
struct CancellationSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/cancellation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::cancellation
