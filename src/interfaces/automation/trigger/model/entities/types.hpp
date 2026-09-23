#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::trigger::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/trigger/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::trigger::model::entities
