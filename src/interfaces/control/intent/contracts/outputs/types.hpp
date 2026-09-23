#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::intent::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/intent/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::intent::contracts::outputs
