#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::constraint::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/constraint/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::constraint::contracts::inputs
