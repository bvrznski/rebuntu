#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::chain {
struct ChainSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/chain";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::chain
