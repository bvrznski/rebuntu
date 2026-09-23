#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::route {
struct RouteSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/route";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::route
