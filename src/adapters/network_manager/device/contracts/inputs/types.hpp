#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::network_manager::device::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/network_manager/device/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::network_manager::device::contracts::inputs
