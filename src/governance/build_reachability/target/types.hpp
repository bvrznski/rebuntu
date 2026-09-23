#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::build_reachability::target {
struct TargetSkeleton final {
    static constexpr std::string_view path = "src/governance/build_reachability/target";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::build_reachability::target
