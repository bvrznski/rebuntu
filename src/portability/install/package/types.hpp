#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::package {
struct PackageSkeleton final {
    static constexpr std::string_view path = "src/portability/install/package";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::package
