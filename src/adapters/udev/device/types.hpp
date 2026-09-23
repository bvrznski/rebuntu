#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::device {
struct DeviceSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/device";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::device
