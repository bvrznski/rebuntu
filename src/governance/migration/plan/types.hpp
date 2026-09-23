#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::plan {
struct PlanSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/plan";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::plan
