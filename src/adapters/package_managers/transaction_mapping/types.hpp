#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::package_managers::transaction_mapping {
struct TransactionMappingSkeleton final {
    static constexpr std::string_view path = "src/adapters/package_managers/transaction_mapping";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::package_managers::transaction_mapping
