#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::subscription::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/subscription/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::subscription::verification::evidence
