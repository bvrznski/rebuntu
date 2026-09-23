#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::goal::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/goal/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::goal::model::entities
