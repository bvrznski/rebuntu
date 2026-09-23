#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::consistency::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/state/consistency/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::consistency::model::entities
