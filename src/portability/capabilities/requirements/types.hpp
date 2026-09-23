#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::capabilities::requirements {
struct RequirementsSkeleton final {
    static constexpr std::string_view path = "src/portability/capabilities/requirements";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::capabilities::requirements
