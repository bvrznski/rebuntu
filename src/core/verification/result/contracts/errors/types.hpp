#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::result::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/verification/result/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::result::contracts::errors
