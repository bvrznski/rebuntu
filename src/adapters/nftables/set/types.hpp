#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::nftables::set {
struct SetSkeleton final {
    static constexpr std::string_view path = "src/adapters/nftables/set";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::nftables::set
