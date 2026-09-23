#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::degradation::recovery {
struct RecoverySkeleton final {
    static constexpr std::string_view path = "src/portability/degradation/recovery";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::degradation::recovery
