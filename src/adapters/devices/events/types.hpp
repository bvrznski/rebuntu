#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::events {
struct EventsSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/events";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::events
