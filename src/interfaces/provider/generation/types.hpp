#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::generation {
struct GenerationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/generation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::generation
