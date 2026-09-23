#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::timeouts::model::value_objects {
struct ValueObjectsSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/timeouts/model/value_objects";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::timeouts::model::value_objects
