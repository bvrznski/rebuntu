#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::power {
struct PowerSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/power";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::power
