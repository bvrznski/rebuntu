#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::provenance::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/provenance/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::provenance::contracts::invariants
