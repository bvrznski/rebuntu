#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::provider_map {
struct ProviderMapSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/provider_map";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::provider_map
