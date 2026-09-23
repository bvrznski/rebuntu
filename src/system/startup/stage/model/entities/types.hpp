#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::stage::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/startup/stage/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::stage::model::entities
