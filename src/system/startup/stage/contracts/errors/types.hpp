#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::startup::stage::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/system/startup/stage/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::startup::stage::contracts::errors
