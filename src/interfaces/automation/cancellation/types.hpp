#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::cancellation {
struct CancellationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/cancellation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::cancellation
