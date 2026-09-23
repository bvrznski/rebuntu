#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::platform_detection::init_system::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/platform_detection/init_system/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::platform_detection::init_system::contracts::inputs
