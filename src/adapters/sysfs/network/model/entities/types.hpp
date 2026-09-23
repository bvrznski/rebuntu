#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::network::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/network/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::network::model::entities
