#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::result {
struct ResultSkeleton final {
    static constexpr std::string_view path = "src/core/verification/result";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::result
