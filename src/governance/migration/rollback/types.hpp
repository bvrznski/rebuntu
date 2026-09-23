#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::rollback {
struct RollbackSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/rollback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::rollback
