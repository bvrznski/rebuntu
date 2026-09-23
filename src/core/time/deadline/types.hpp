#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::deadline {
struct DeadlineSkeleton final {
    static constexpr std::string_view path = "src/core/time/deadline";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::deadline
