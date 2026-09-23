#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::recovery::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/recovery/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::recovery::contracts::outputs
