#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::properties {
struct PropertiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/properties";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::properties
