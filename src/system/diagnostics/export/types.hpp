#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node {
struct ExportNodeSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node
