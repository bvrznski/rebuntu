#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::response::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/response/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::response::verification::assertions
