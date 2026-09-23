#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::capabilities {
struct CapabilitiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/capabilities";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::capabilities
