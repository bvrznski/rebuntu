#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::transfer {
struct TransferSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/transfer";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::transfer
