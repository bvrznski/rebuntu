#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::architecture_audit::inventory::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/architecture_audit/inventory/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::architecture_audit::inventory::contracts::errors
