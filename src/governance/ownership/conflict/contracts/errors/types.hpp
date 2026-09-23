#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::conflict::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/conflict/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::conflict::contracts::errors
