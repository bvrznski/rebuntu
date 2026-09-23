#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::transaction {
struct TransactionSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/transaction";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::transaction
