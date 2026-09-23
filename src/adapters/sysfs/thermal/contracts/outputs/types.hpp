#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::thermal::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/thermal/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::thermal::contracts::outputs
