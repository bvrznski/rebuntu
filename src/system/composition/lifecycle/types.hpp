#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::lifecycle {
struct LifecycleSkeleton final {
    static constexpr std::string_view path = "src/system/composition/lifecycle";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::lifecycle
