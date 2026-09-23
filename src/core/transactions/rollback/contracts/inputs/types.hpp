#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::rollback::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/rollback/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::rollback::contracts::inputs
