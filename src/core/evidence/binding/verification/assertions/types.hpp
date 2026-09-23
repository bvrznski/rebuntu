#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::binding::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/binding/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::binding::verification::assertions
