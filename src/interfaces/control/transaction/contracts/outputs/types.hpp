#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::transaction::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/transaction/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::transaction::contracts::outputs
