#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::code {
struct CodeSkeleton final {
    static constexpr std::string_view path = "src/core/errors/code";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::code
