#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::limits::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/limits/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::limits::model::entities
