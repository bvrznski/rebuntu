#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::constraint::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/constraint/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::constraint::contracts::outputs
