#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::health::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/health/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::health::contracts::errors
