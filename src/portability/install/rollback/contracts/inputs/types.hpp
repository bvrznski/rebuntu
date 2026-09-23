#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::rollback::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/portability/install/rollback/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::rollback::contracts::inputs
