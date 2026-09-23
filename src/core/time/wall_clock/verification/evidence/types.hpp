#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::wall_clock::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/time/wall_clock/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::wall_clock::verification::evidence
