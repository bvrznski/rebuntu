#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::fallback {
struct FallbackSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/fallback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::fallback
