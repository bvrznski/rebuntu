#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::diagnostic::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/result/diagnostic/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::diagnostic::contracts::inputs
