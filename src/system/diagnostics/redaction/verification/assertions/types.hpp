#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::redaction::verification::assertions {
struct AssertionsSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/redaction/verification/assertions";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::redaction::verification::assertions
