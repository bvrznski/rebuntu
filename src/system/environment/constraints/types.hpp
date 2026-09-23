#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::environment::constraints {
struct ConstraintsSkeleton final {
    static constexpr std::string_view path = "src/system/environment/constraints";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::environment::constraints
