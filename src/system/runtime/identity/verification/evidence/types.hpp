#pragma once

#include <string_view>

namespace rebuntu::skeleton::system::runtime::identity::verification::evidence {
struct EvidenceSkeleton final {
    static constexpr std::string_view path = "src/system/runtime/identity/verification/evidence";
    static constexpr bool behavioral_implementation = false;
};
}  // namespace rebuntu::skeleton::system::runtime::identity::verification::evidence
