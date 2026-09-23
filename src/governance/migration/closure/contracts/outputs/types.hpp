#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::closure::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/closure/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::closure::contracts::outputs
