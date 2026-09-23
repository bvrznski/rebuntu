#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::network {
struct NetworkSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/network";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::network
