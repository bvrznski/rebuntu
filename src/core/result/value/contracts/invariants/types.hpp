#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::value::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/result/value/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::value::contracts::invariants
