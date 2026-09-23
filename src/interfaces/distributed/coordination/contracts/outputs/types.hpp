#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::distributed::coordination::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/distributed/coordination/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::distributed::coordination::contracts::outputs
