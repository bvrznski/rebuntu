#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::suite::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/suite/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::suite::contracts::outputs
