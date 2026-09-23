#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::policy {
struct PolicySkeleton final {
    static constexpr std::string_view path = "src/system/shell/policy";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::policy
