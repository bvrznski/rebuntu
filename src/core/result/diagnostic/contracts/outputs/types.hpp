#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::diagnostic::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/result/diagnostic/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::diagnostic::contracts::outputs
