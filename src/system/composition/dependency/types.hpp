#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::dependency {
struct DependencySkeleton final {
    static constexpr std::string_view path = "src/system/composition/dependency";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::dependency
