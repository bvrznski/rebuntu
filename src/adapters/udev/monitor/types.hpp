#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::monitor {
struct MonitorSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/monitor";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::monitor
