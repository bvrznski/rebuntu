#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::caller_map {
struct CallerMapSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/caller_map";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::caller_map
