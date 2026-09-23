#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::error::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/error/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::error::verification::assertions
