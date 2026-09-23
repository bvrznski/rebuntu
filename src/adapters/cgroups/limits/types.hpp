#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::limits {
struct LimitsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/limits";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::limits
