#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::platform_detection::virtualization::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/portability/platform_detection/virtualization/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::platform_detection::virtualization::contracts::errors
