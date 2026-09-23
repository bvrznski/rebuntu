#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::observation::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/units/observation/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::observation::contracts::inputs
