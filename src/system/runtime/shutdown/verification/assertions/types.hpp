#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::shutdown::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/shutdown/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::shutdown::verification::assertions
