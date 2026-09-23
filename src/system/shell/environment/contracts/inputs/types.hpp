#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::environment::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/shell/environment/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::environment::contracts::inputs
