#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::configuration::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/portability/install/configuration/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::configuration::contracts::outputs
