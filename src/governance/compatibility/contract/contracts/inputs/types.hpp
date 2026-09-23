#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::contract::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/contract/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::contract::contracts::inputs
