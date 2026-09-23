#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::freshness {
struct FreshnessSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/freshness";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::freshness
