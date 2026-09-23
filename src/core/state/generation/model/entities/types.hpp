#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::generation::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/state/generation/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::generation::model::entities
