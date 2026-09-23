#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::claims {
struct ClaimsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/claims";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::claims
