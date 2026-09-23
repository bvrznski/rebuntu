#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::ruleset::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/ruleset/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::ruleset::contracts::inputs
