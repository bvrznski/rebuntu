#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::native::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/native/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::native::contracts::inputs
