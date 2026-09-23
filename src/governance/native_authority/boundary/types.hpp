#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::boundary {
struct BoundarySkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/boundary";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::boundary
