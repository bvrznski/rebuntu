#pragma once

#include <string_view>

namespace rebuntu::skeleton::core::identity::scope::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/core/identity/scope/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::core::identity::scope::contracts::outputs
