#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::procfs::identity_tokens {
struct IdentityTokensSkeleton final {
    static constexpr std::string_view path = "src/adapters/procfs/identity_tokens";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::procfs::identity_tokens
