#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::plan::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/plan/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::plan::model::entities
