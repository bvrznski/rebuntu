#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::failure::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/failure/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::failure::model::entities
