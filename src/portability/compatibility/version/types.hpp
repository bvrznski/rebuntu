#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::version {
struct VersionSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/version";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::version
