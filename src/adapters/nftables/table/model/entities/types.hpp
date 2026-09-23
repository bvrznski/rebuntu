#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::table::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/table/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::table::model::entities
