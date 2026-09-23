#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::rule {
struct RuleSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/rule";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::rule
