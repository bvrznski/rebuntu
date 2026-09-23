#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::step::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/step/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::step::verification::evidence
