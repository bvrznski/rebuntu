#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::dbus::error_mapping::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/dbus/error_mapping/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::dbus::error_mapping::model::entities
