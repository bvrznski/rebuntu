#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::result::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/shell/result/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::result::contracts::outputs
