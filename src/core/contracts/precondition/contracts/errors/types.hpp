#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::precondition::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/precondition/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::precondition::contracts::errors
