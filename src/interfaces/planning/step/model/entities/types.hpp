#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::step::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/step/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::step::model::entities
