#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::provider_map::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/provider_map/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::provider_map::verification::evidence
