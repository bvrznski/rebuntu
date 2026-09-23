#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::rollback::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/rollback/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::rollback::model::entities
