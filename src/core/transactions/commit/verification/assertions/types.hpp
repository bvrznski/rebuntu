#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::commit::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/commit/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::commit::verification::assertions
