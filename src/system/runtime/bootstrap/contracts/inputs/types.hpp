#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::bootstrap::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/bootstrap/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::bootstrap::contracts::inputs
