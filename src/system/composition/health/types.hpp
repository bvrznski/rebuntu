#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::composition::health {
struct HealthSkeleton final {
    static constexpr std::string_view path = "src/system/composition/health";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::composition::health
