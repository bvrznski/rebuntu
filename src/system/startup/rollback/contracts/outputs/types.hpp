#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::rollback::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/startup/rollback/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::rollback::contracts::outputs
