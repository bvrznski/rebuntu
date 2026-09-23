#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::sequence {
struct SequenceSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/sequence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::sequence
