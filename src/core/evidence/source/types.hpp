#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::source {
struct SourceSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/source";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::source
