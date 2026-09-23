#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::cgroups::controller {
struct ControllerSkeleton final {
    static constexpr std::string_view path = "src/adapters/cgroups/controller";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::cgroups::controller
