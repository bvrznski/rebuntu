#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::group {
struct GroupSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/group";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::group
