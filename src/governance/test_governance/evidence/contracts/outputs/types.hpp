#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::evidence::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/evidence/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::evidence::contracts::outputs
