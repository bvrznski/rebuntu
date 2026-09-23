#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::socket {
struct SocketSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/socket";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::socket
