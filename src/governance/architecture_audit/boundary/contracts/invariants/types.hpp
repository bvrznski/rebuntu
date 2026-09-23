#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::boundary::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/boundary/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::boundary::contracts::invariants
