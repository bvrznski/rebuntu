#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::planning::step {
struct StepSkeleton final {
    static constexpr std::string_view path = "src/interfaces/planning/step";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::planning::step
