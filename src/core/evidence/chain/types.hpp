#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::evidence::chain {
struct ChainSkeleton final {
    static constexpr std::string_view path = "src/core/evidence/chain";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::evidence::chain
