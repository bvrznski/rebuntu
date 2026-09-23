#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::provider::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/provider/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::provider::verification::assertions
