#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::provider_selection::compatibility::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/provider_selection/compatibility/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::provider_selection::compatibility::contracts::inputs
