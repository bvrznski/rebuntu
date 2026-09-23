#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::component::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/composition/component/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::component::verification::assertions
