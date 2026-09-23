#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::operation::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/operation/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::operation::contracts::errors
