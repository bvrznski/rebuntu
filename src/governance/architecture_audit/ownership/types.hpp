#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::ownership {
struct OwnershipSkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/ownership";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::ownership
