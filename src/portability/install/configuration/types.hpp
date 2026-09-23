#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::configuration {
struct ConfigurationSkeleton final {
    static constexpr std::string_view path = "src/portability/install/configuration";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::configuration
