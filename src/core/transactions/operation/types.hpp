#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::operation {
struct OperationSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/operation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::operation
