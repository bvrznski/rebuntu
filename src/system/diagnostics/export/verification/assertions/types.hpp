#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::export_node::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/export/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::export_node::verification::assertions
