#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::message {
struct MessageSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/message";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::message
