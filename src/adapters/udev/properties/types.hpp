#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::udev::properties {
struct PropertiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/udev/properties";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::udev::properties
