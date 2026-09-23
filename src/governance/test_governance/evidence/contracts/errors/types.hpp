#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::test_governance::evidence::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/governance/test_governance/evidence/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::test_governance::evidence::contracts::errors
