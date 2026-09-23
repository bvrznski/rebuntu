#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::state::consistency::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/state/consistency/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::state::consistency::verification::assertions
