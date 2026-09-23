#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::generation::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/core/state/generation/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::generation::verification::assertions
