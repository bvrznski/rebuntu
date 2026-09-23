#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::platform_detection::init_system {
struct InitSystemSkeleton final {
    static constexpr std::string_view path = "src/portability/platform_detection/init_system";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::platform_detection::init_system
