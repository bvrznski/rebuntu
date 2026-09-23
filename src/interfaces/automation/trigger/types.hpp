#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::trigger {
struct TriggerSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/trigger";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::trigger
