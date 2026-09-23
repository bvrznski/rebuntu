#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::contract {
struct ContractSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/contract";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::contract
