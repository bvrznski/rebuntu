#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::migration::rollback {
struct RollbackSkeleton final {
    static constexpr std::string_view path = "src/portability/migration/rollback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::migration::rollback
