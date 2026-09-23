#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::generation {
struct GenerationSkeleton final {
    static constexpr std::string_view path = "src/core/identity/generation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::generation
