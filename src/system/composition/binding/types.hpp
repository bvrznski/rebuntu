#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::binding {
struct BindingSkeleton final {
    static constexpr std::string_view path = "src/system/composition/binding";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::binding
