#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::status::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/status/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::status::contracts::outputs
