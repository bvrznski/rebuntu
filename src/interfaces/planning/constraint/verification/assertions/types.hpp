#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::constraint::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/constraint/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::constraint::verification::assertions
