#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::matching::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/matching/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::matching::verification::evidence
