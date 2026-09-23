#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::generation::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/generation/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::generation::contracts::inputs
