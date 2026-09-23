#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::operation::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/operation/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::operation::contracts::invariants
