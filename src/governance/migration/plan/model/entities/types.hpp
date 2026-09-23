#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::plan::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/plan/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::plan::model::entities
