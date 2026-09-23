#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::intent::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/intent/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::intent::contracts::inputs
