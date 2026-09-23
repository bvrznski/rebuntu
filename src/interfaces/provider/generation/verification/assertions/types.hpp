#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::generation::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/generation/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::generation::verification::assertions
