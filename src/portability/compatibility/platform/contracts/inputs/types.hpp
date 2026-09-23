#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::platform::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/platform/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::platform::contracts::inputs
