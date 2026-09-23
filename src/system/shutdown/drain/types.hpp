#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::shutdown::drain {
struct DrainSkeleton final {
    static constexpr std::string_view path = "src/system/shutdown/drain";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::shutdown::drain
