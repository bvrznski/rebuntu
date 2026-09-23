#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::evidence::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/evidence/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::evidence::contracts::inputs
