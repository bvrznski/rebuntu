#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::events::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/events/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::events::model::entities
