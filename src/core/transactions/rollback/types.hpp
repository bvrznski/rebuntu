#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::rollback {
struct RollbackSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/rollback";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::rollback
