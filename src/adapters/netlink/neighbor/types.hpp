#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::neighbor {
struct NeighborSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/neighbor";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::neighbor
