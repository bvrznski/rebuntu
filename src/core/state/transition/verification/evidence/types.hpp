#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::state::transition::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/state/transition/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::state::transition::verification::evidence
