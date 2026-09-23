#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::coordination::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/coordination/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::coordination::verification::assertions
