#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::events::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/events/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::events::contracts::outputs
