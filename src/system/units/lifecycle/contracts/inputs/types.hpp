#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::lifecycle::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/units/lifecycle/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::lifecycle::contracts::inputs
