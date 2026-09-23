#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::platform {
struct PlatformSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/platform";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::platform
