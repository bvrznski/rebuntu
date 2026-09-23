#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::compensation::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/compensation/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::compensation::verification::assertions
