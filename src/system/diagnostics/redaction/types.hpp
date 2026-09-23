#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::diagnostics::redaction {
struct RedactionSkeleton final {
    static constexpr std::string_view path = "src/system/diagnostics/redaction";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::diagnostics::redaction
