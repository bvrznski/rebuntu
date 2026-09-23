#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::coordination {
struct CoordinationSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/coordination";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::coordination
