#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::compatibility::provider::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/portability/compatibility/provider/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::compatibility::provider::contracts::invariants
