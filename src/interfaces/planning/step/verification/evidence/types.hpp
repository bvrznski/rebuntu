#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::step::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/step/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::step::verification::evidence
