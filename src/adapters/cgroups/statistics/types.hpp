#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::statistics {
struct StatisticsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/statistics";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::statistics
