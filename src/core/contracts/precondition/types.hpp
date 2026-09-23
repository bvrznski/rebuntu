#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::precondition {
struct PreconditionSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/precondition";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::precondition
