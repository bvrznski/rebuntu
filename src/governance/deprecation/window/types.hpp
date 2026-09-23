#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::deprecation::window {
struct WindowSkeleton final {
    static constexpr std::string_view path = "src/governance/deprecation/window";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::deprecation::window
