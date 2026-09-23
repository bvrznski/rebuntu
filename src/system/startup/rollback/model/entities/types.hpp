#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::rollback::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/system/startup/rollback/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::rollback::model::entities
