#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::profile::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/profile/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::profile::contracts::outputs
