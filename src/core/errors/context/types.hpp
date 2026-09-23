#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::context {
struct ContextSkeleton final {
    static constexpr std::string_view path = "src/core/errors/context";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::context
