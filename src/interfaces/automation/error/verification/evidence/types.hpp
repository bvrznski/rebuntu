#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::error::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/error/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::error::verification::evidence
