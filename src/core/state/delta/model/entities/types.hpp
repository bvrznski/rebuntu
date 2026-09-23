#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::delta::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/state/delta/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::delta::model::entities
