#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::resolver::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/core/identity/resolver/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::resolver::verification::evidence
