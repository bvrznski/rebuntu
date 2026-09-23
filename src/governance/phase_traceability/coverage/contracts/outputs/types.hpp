#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::phase_traceability::coverage::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/phase_traceability/coverage/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::phase_traceability::coverage::contracts::outputs
