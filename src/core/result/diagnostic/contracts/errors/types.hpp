#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::result::diagnostic::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/result/diagnostic/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::result::diagnostic::contracts::errors
