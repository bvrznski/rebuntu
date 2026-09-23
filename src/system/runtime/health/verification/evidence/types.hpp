#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::health::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/health/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::health::verification::evidence
