#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::error::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/error/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::error::model::entities
