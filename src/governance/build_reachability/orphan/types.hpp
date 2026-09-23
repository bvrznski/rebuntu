#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::build_reachability::orphan {
struct OrphanSkeleton final {
    static constexpr std::string_view path = "src/governance/build_reachability/orphan";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::build_reachability::orphan
