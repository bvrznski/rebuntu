#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node::contracts::invariants {
struct InvariantsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export/contracts/invariants";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node::contracts::invariants
