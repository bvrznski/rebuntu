#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::network::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/network/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::network::contracts::invariants
