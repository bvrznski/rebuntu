#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::error::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/result/error/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::error::contracts::invariants
