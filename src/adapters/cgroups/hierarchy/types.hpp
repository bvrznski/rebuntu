#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::hierarchy {
struct HierarchySkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/hierarchy";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::hierarchy
