#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::transactions::checkpoint {
struct CheckpointSkeleton final {
    static constexpr std::string_view path = "src/core/transactions/checkpoint";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::transactions::checkpoint
