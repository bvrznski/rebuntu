#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::plan::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/plan/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::plan::verification::evidence
