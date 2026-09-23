#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::stage::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/stage/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::stage::verification::assertions
