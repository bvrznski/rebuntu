#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::fallback::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/fallback/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::fallback::contracts::inputs
