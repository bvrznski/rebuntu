#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::invariant_audit::report::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/invariant_audit/report/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::invariant_audit::report::contracts::outputs
