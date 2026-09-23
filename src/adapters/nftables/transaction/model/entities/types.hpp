#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::transaction::model::entities {
struct EntitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/transaction/model/entities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::transaction::model::entities
