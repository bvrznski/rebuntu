#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::errors::code::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/errors/code/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::errors::code::contracts::invariants
