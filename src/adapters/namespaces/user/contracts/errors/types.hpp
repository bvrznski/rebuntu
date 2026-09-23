#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::namespaces::user::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/namespaces/user/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::namespaces::user::contracts::errors
