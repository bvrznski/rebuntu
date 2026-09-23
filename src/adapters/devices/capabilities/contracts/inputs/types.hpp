#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::devices::capabilities::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/devices/capabilities/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::devices::capabilities::contracts::inputs
