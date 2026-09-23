#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::statistics::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/statistics/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::statistics::model::entities
