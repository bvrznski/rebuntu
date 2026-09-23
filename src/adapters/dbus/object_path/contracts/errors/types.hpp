#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::object_path::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/object_path/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::object_path::contracts::errors
