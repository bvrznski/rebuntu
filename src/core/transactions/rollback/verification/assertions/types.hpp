#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::rollback::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/rollback/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::rollback::verification::assertions
