#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::address::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/address/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::address::contracts::outputs
