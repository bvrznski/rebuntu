#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::phase_traceability::gap {
struct GapSkeleton final {
    static constexpr std::string_view path = "src/governance/phase_traceability/gap";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::phase_traceability::gap
