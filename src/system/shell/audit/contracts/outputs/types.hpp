#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::audit::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/shell/audit/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::audit::contracts::outputs
