#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::response::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/response/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::response::model::entities
