#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::prerequisite {
struct PrerequisiteSkeleton final {
    static constexpr std::string_view path = "src/portability/install/prerequisite";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::prerequisite
