#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::constraints::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/constraints/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::constraints::verification::assertions
