#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::transaction::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/transaction/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::transaction::verification::assertions
