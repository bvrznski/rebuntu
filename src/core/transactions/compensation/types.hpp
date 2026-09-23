#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::compensation {
struct CompensationSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/compensation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::compensation
