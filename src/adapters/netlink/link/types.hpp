#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::link {
struct LinkSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/link";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::link
