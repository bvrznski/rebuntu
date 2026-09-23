#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::build_reachability::dependency {
struct DependencySkeleton final {
    static constexpr std::string_view path = "src/governance/build_reachability/dependency";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::build_reachability::dependency
