#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::discovery {
struct DiscoverySkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/discovery";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::discovery
