#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::request::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/request/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::request::verification::assertions
