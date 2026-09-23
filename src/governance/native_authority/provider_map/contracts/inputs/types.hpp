#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::native_authority::provider_map::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/governance/native_authority/provider_map/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::native_authority::provider_map::contracts::inputs
