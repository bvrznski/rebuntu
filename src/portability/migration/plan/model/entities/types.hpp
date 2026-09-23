#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::plan::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/plan/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::plan::model::entities
