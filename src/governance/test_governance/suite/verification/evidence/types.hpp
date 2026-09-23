#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::suite::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/suite/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::suite::verification::evidence
