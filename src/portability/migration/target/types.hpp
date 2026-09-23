#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::target {
struct TargetSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/target";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::target
