#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::source {
struct SourceSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/source";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::source
