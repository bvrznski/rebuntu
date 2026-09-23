#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::inventory::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/inventory/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::inventory::contracts::outputs
