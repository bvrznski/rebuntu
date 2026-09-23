#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::address::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/address/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::address::contracts::inputs
