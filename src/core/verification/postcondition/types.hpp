#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::postcondition {
struct PostconditionSkeleton final {
    static constexpr std::string_view path = "src/core/verification/postcondition";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::postcondition
