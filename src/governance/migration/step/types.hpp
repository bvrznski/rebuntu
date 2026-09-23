#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::step {
struct StepSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/step";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::step
