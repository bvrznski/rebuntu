#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::units::lifecycle::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/units/lifecycle/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::units::lifecycle::contracts::outputs
