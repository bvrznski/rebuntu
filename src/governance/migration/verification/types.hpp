#pragma once

#include <string_view>

namespace rebuntu::skeleton::governance::migration::verification {
struct VerificationSkeleton final {
    static constexpr std::string_view path = "src/governance/migration/verification";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::governance::migration::verification
