#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::transfer::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/transfer/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::transfer::contracts::errors
