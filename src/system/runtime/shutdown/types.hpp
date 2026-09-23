#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::shutdown {
struct ShutdownSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/shutdown";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::shutdown
