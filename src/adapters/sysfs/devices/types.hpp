#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::devices {
struct DevicesSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/devices";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::devices
