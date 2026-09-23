#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::control::transaction {
struct TransactionSkeleton final {
    static constexpr std::string_view path = "src/interfaces/control/transaction";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::control::transaction
