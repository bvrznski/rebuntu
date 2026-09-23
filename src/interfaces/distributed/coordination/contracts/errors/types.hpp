#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::coordination::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/coordination/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::coordination::contracts::errors
