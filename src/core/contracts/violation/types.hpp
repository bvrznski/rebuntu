#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::contracts::violation {
struct ViolationSkeleton final {
    static constexpr std::string_view path = "src/core/contracts/violation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::contracts::violation
