#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::properties {
struct PropertiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/properties";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::properties
