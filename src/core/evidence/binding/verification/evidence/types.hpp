#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::binding::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/binding/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::binding::verification::evidence
