#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::netlink::attributes {
struct AttributesSkeleton final {
    static constexpr std::string_view path = "src/adapters/netlink/attributes";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::netlink::attributes
