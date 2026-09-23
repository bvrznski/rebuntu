#pragma once

#include <string_view>

namespace rebuntu::skeleton::portability::setup::validation::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/portability/setup/validation/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::portability::setup::validation::contracts::invariants
