#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::recovery::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/recovery/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::recovery::verification::assertions
