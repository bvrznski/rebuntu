#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::error::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/error/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::error::contracts::inputs
