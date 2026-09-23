#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::platform_detection::container::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/platform_detection/container/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::platform_detection::container::verification::assertions
