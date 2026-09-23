#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::install::rollback {
struct RollbackSkeleton final {
    static constexpr std::string_view path = "src/portability/install/rollback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::install::rollback
