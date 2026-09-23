#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::ownership::validation {
struct ValidationSkeleton final {
    static constexpr std::string_view path = "src/governance/ownership/validation";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::ownership::validation
