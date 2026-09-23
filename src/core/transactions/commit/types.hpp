#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::commit {
struct CommitSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/commit";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::commit
