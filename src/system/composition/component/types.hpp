#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::component {
struct ComponentSkeleton final {
    static constexpr std::string_view path = "src/system/composition/component";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::component
