#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::method_call::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/method_call/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::method_call::model::entities
