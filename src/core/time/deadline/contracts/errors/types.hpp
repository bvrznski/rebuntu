#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::time::deadline::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/time/deadline/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::time::deadline::contracts::errors
