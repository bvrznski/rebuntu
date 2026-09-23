#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::constraint::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/constraint/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::constraint::model::entities
