#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::audit {
struct AuditSkeleton final {
    static constexpr std::string_view path = "src/system/shell/audit";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::audit
