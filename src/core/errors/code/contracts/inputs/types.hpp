#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::code::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/errors/code/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::code::contracts::inputs
