#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::ruleset::contracts::errors {
struct ErrorsSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/ruleset/contracts/errors";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::ruleset::contracts::errors
