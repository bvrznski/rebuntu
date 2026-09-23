#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::liveness {
struct LivenessSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/liveness";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::liveness
