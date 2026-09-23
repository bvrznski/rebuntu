#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::identity {
struct IdentitySkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/identity";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::identity
