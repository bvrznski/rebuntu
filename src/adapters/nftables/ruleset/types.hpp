#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::ruleset {
struct RulesetSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/ruleset";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::ruleset
