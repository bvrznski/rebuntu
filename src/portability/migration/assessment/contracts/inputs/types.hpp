#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::assessment::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/assessment/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::assessment::contracts::inputs
