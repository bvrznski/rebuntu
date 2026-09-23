#pragma once

#include <string_view>

namespace rebuntu::skeleton::adapters::polkit::decision {
struct DecisionSkeleton final {
    static constexpr std::string_view path = "src/adapters/polkit/decision";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::adapters::polkit::decision
