#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::invariant_audit::probe::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/governance/invariant_audit/probe/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::invariant_audit::probe::contracts::inputs
