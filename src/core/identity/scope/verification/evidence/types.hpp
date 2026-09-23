#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::scope::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/identity/scope/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::scope::verification::evidence
