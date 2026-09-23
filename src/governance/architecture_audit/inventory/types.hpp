#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::inventory {
struct InventorySkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/inventory";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::inventory
