#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::thermal {
struct ThermalSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/thermal";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::thermal
