#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::invariant::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/invariant/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::invariant::contracts::inputs
