#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::lease {
struct LeaseSkeleton final {
    static constexpr std::string_view path = "src/core/time/lease";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::lease
