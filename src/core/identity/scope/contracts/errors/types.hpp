#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::scope::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/core/identity/scope/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::scope::contracts::errors
