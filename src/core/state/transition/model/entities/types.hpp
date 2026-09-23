#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::transition::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/state/transition/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::transition::model::entities
