#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::plan::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/plan/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::plan::contracts::outputs
