#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::journal {
struct JournalSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/journal";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::journal
