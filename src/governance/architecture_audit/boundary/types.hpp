#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::boundary {
struct BoundarySkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/boundary";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::boundary
