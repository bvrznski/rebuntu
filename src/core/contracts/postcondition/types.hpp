#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::postcondition {
struct PostconditionSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/postcondition";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::postcondition
