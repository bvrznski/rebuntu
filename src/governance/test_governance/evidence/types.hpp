#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::evidence
