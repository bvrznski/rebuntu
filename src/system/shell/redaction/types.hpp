#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::redaction {
struct RedactionSkeleton final {
    static constexpr std::string_view path = "src/system/shell/redaction";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::redaction
