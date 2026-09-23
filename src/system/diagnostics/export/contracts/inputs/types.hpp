#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node::contracts::inputs
