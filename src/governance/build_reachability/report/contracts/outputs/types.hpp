#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::build_reachability::report::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/build_reachability/report/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::build_reachability::report::contracts::outputs
