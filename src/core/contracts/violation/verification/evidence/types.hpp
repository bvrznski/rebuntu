#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::violation::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/violation/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::violation::verification::evidence
