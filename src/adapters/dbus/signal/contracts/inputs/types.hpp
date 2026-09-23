#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::signal::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/signal/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::signal::contracts::inputs
