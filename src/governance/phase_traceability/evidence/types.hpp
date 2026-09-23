#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::phase_traceability::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/governance/phase_traceability/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::phase_traceability::evidence
