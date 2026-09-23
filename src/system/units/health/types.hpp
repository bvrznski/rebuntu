#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::health {
struct HealthSkeleton final {
    static constexpr std::string_view path = "src/system/units/health";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::health
