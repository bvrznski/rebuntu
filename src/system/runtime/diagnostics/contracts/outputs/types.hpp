#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::diagnostics::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/diagnostics/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::diagnostics::contracts::outputs
