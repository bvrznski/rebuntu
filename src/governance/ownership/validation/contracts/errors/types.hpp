#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::validation::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/validation/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::validation::contracts::errors
