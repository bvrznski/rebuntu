#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::report::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/report/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::report::contracts::invariants
