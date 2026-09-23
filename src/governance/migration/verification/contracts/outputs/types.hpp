#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::verification::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/verification/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::verification::contracts::outputs
