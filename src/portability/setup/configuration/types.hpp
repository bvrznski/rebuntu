#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::configuration {
struct ConfigurationSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/configuration";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::configuration
