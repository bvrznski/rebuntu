#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::stage::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/startup/stage/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::stage::contracts::outputs
