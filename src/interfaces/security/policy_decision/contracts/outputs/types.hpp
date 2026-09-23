#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::policy_decision::contracts::outputs {
struct OutputsSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/policy_decision/contracts/outputs";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::policy_decision::contracts::outputs
