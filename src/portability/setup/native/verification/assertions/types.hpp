#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::native::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/native/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::native::verification::assertions
