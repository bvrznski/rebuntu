#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::events::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/events/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::events::model::entities
