#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::error_mapping::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/error_mapping/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::error_mapping::contracts::inputs
