#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::contract::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/contract/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::contract::model::entities
