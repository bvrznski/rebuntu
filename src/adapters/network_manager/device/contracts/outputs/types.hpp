#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::device::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/device/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::device::contracts::outputs
