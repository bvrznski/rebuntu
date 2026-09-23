#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::constraint::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/constraint/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::constraint::model::entities
