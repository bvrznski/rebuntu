#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::host_safety::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/host_safety/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::host_safety::contracts::outputs
