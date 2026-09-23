#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::profile::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/profile/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::profile::verification::assertions
