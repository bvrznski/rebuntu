#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::binding::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/composition/binding/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::binding::verification::assertions
