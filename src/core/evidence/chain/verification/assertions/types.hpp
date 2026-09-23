#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::chain::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/chain/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::chain::verification::assertions
