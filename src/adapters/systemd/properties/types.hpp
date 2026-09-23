#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::systemd::properties {
struct PropertiesSkeleton final {
    static constexpr std::string_view path = "src/adapters/systemd/properties";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::systemd::properties
