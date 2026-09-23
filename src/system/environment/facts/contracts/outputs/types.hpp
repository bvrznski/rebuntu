#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::facts::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/facts/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::facts::contracts::outputs
