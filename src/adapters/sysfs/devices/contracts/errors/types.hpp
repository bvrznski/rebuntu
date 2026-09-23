#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::sysfs::devices::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/sysfs/devices/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::sysfs::devices::contracts::errors
