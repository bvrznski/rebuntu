#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::checkpoint::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/checkpoint/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::checkpoint::contracts::outputs
