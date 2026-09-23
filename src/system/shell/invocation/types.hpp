#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shell::invocation {
struct InvocationSkeleton final {
    static constexpr std::string_view path = "src/system/shell/invocation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shell::invocation
