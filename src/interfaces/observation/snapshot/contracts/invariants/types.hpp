#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::snapshot::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/snapshot/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::snapshot::contracts::invariants
