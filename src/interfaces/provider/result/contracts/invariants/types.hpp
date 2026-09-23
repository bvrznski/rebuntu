#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::provider::result::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/provider/result/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::provider::result::contracts::invariants
