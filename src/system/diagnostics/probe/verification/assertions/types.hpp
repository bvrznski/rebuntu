#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::probe::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/probe/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::probe::verification::assertions
