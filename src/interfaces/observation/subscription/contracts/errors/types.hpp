#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::observation::subscription::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/observation/subscription/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::observation::subscription::contracts::errors
