#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::error::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/error/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::error::contracts::errors
