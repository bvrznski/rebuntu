#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::failure::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/system/startup/failure/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::failure::contracts::errors
