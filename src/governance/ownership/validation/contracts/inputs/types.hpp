#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::validation::contracts::inputs {
struct InputsSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/validation/contracts/inputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::validation::contracts::inputs
