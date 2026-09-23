#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::socket::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/socket/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::socket::verification::assertions
