#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::monitor::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/monitor/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::monitor::model::entities
