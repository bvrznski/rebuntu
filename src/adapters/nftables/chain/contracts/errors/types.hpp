#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::chain::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/chain/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::chain::contracts::errors
