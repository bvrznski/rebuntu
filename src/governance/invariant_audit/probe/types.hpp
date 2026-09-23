#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::invariant_audit::probe {
struct ProbeSkeleton final {
    static constexpr std::string_view path = "src/governance/invariant_audit/probe";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::invariant_audit::probe
