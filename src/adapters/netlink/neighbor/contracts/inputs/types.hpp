#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::neighbor::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/neighbor/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::neighbor::contracts::inputs
