#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::result::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/verification/result/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::result::contracts::inputs
