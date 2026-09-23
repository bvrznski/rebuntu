#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::boundary {
struct BoundarySkeleton final {
    static constexpr std::string_view path = "src/system/shell/boundary";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::boundary
