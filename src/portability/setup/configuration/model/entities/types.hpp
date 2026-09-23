#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::configuration::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/configuration/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::configuration::model::entities
