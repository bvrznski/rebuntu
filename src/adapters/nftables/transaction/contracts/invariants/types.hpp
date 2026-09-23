#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::transaction::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/transaction/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::transaction::contracts::invariants
