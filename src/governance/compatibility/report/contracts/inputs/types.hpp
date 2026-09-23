#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::compatibility::report::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/governance/compatibility/report/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::compatibility::report::contracts::inputs
