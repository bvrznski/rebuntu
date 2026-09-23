#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::environment {
struct EnvironmentSkeleton final {
    static constexpr std::string_view path = "src/system/shell/environment";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::environment
