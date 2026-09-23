#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::constraints {
struct ConstraintsSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/constraints";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::constraints
