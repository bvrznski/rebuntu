#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::flakiness {
struct FlakinessSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/flakiness";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::flakiness
