#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::provider_selection::candidate {
struct CandidateSkeleton final {
    static constexpr std::string_view path = "src/portability/provider_selection/candidate";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::provider_selection::candidate
