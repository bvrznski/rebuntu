#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::automation::status {
struct StatusSkeleton final {
    static constexpr std::string_view path = "src/interfaces/automation/status";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::automation::status
