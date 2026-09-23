#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::controller::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/controller/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::controller::contracts::outputs
