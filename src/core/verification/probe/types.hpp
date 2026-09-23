#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::verification::probe {
struct ProbeSkeleton final {
    static constexpr std::string_view path = "src/core/verification/probe";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::verification::probe
