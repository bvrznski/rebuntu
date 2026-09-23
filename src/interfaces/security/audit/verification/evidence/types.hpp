#pragma once

#include <string_view>

namespace rebuntu::skeleton::interfaces::security::audit::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/interfaces/security/audit/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::interfaces::security::audit::verification::evidence
