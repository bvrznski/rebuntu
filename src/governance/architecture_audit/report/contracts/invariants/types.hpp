#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::report::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/report/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::report::contracts::invariants
