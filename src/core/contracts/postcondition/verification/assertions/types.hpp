#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::postcondition::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/postcondition/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::postcondition::verification::assertions
