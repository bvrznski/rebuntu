#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::provenance::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/provenance/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::provenance::verification::evidence
