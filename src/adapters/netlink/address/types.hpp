#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::address {
struct AddressSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/address";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::address
