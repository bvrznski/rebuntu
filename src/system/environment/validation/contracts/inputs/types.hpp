#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::validation::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/validation/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::validation::contracts::inputs
