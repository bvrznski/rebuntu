#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::verification::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/verification/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::verification::contracts::inputs
