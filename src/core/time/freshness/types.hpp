#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::freshness {
struct FreshnessSkeleton final {
    static constexpr std::string_view path = "src/core/time/freshness";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::freshness
