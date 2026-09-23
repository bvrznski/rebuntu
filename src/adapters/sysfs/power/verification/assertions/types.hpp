#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::power::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/power/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::power::verification::assertions
