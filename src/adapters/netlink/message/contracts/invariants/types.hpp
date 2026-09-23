#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::message::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/message/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::message::contracts::invariants
