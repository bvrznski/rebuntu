#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::recovery::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/recovery/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::recovery::verification::assertions
