#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::provider_selection::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/portability/provider_selection/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::provider_selection::evidence
