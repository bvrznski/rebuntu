#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::freshness::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/freshness/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::freshness::contracts::inputs
